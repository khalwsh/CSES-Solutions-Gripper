/**
 * Author : Khalwsh
 * Usage:
 *  node CSES-scrapper.js --username YOUR_USERNAME --password YOUR_PASSWORD --out ./cses_solutions --headless true
 */

const puppeteer = require('puppeteer');
const fs = require('fs-extra');
const path = require('path');
const yargs = require('yargs/yargs');
const {
    hideBin
} = require('yargs/helpers');

const argv = yargs(hideBin(process.argv))
    .option('username', {
        type: 'string',
        demandOption: true
    })
    .option('password', {
        type: 'string',
        demandOption: true
    })
    .option('out', {
        type: 'string',
        default: './cses_solutions'
    })
    .option('headless', {
        type: 'boolean',
        default: true
    })
    .option('delay', {
        type: 'number',
        default: 700
    }) 
    .argv;

function safeName(s) {
    if (!s) return 'Unknown';
    return s.replace(/[\/\\:*?"<>|]/g, '').replace(/\s+/g, ' ').trim();
}

function guessExtFromLang(lang) {
    if (!lang) return '.txt';
    lang = lang.toLowerCase();
    if (lang.includes('c++') || lang.includes('cpp')) return '.cpp';
    if (lang.includes('c#')) return '.cs';
    if (lang.includes('java')) return '.java';
    if (lang.includes('python')) return '.py';
    if (lang.includes('pascal')) return '.pas';
    if (lang.includes('go')) return '.go';
    if (lang.includes('rust')) return '.rs';
    if (lang.includes('c11') || lang === 'c') return '.c';
    return '.txt';
}

function absoluteUrl(href) {
    if (!href) return href;
    if (href.startsWith('http')) return href;
    if (href.startsWith('/')) return 'https://cses.fi' + href;
    return 'https://cses.fi/' + href;
}

function isAcceptedText(txt) {
    if (!txt) return false;
    return /Accepted|OK|Correct/i.test(txt);
}

async function sleep(page, ms) {
    if (page && typeof page.waitForTimeout === 'function') {
        return page.waitForTimeout(ms);
    }
    return new Promise(resolve => setTimeout(resolve, ms));
}

(async () => {
    const browser = await puppeteer.launch({
        headless: argv.headless,
        args: ['--no-sandbox', '--disable-setuid-sandbox']
    });
    const page = await browser.newPage();
    await page.setUserAgent('Mozilla/5.0 (compatible; cses-ac-downloader/1.0)');

    try {
        console.log('Opening login page...');
        await page.goto('https://cses.fi/login/', {
            waitUntil: 'networkidle2'
        });

        // find visible username/password inputs
        const usernameSelectors = ['input[name="username"]', 'input[name="login"]', 'input[type="text"]'];
        const passwordSelectors = ['input[name="password"]', 'input[type="password"]'];

        const findVisible = async (selectors) => {
            for (const sel of selectors) {
                const el = await page.$(sel);
                if (!el) continue;
                try {
                    const box = await el.boundingBox();
                    if (box) return sel;
                } catch (e) {
                    /* ignore */ }
            }
            return null;
        };

        const userSel = (await findVisible(usernameSelectors)) || 'input[type="text"]';
        const passSel = (await findVisible(passwordSelectors)) || 'input[type="password"]';

        console.log(`Typing username into ${userSel} and password into ${passSel}...`);
        try {
            await page.click(userSel);
            await page.keyboard.type(argv.username, {
                delay: 30
            });
        } catch (e) {
            console.warn('Could not click username selector; attempting direct type.');
            await page.type(userSel, argv.username);
        }
        try {
            await page.click(passSel);
            await page.keyboard.type(argv.password, {
                delay: 30
            });
        } catch (e) {
            console.warn('Could not click password selector; attempting direct type.');
            await page.type(passSel, argv.password);
        }

        // submit
        const submitSelectors = ['button[type="submit"]', 'input[type="submit"]', 'button[name="login"]', 'form button'];
        let submitted = false;
        for (const s of submitSelectors) {
            const el = await page.$(s);
            if (el) {
                await Promise.all([page.waitForNavigation({
                    waitUntil: 'networkidle2'
                }), el.click()]);
                submitted = true;
                break;
            }
        }
        if (!submitted) {
            await page.keyboard.press('Enter');
            await page.waitForNavigation({
                waitUntil: 'networkidle2'
            });
        }

        // quick check for login errors
        const bodyTextAfterLogin = await page.evaluate(() => document.body.innerText || '');
        if (/incorrect|invalid/i.test(bodyTextAfterLogin) || page.url().includes('/login')) {
            if (/incorrect|invalid/i.test(bodyTextAfterLogin)) {
                throw new Error('Login failed: incorrect credentials or blocked.');
            } else {
                console.warn('Login page still open — continuing, but check manually if logged in.');
            }
        }
        console.log('Login step finished. Current page:', page.url());

        // 1) open problemset and build problem map
        console.log('Opening problemset page...');
        await page.goto('https://cses.fi/problemset/', {
            waitUntil: 'networkidle2'
        });

        // extract problem metadata
        const problemMap = await page.evaluate(() => {
            const map = {};
            const headings = Array.from(document.querySelectorAll('h2, h3, h4')).filter(h => h.innerText.trim().length > 0);
            for (const h of headings) {
                const section = h.innerText.trim();
                let el = h.nextElementSibling;
                let steps = 0;
                while (el && steps < 8) {
                    const anchors = el.querySelectorAll ? Array.from(el.querySelectorAll('a')) : [];
                    if (anchors.length > 0) {
                        for (const a of anchors) {
                            const href = a.getAttribute('href') || '';
                            const m = href.match(/(\d+)/);
                            if (m) {
                                const pid = m[1];
                                const title = a.innerText.trim() || a.getAttribute('title') || ('Problem ' + pid);
                                const full = href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/problemset/' + href);
                                if (!map[pid]) map[pid] = {
                                    section,
                                    title,
                                    href: full
                                };
                            }
                        }
                        break;
                    }
                    el = el.nextElementSibling;
                    steps++;
                }
            }
            // fallback: pick anchors anywhere
            if (Object.keys(map).length === 0) {
                const all = Array.from(document.querySelectorAll('a'));
                for (const a of all) {
                    const href = a.getAttribute('href') || '';
                    const m = href.match(/(\d+)/);
                    if (m) {
                        const pid = m[1];
                        if (!map[pid]) map[pid] = {
                            section: 'Unknown',
                            title: a.innerText.trim() || ('Problem ' + pid),
                            href: href.startsWith('http') ? href : ('https://cses.fi' + href)
                        };
                    }
                }
            }
            return map;
        });

        const allPids = Object.keys(problemMap);
        console.log(`Problem map collected for ${allPids.length} problems (approx).`);

        // 2) detect solved (green) problems on problemset page
        const solvedList = await page.evaluate(() => {
            const solved = [];
            const anchors = Array.from(document.querySelectorAll('a'));
            const isGreen = (el) => {
                try {
                    const cs = window.getComputedStyle(el);
                    if (!cs || !cs.color) return false;
                    const rgb = cs.color.match(/rgb\((\d+),\s*(\d+),\s*(\d+)\)/);
                    if (!rgb) return false;
                    const r = parseInt(rgb[1], 10),
                        g = parseInt(rgb[2], 10),
                        b = parseInt(rgb[3], 10);
                    return g > 100 && g > r && g > b;
                } catch (e) {
                    return false;
                }
            };

            for (const a of anchors) {
                const href = a.getAttribute('href') || '';
                const m = href.match(/(\d+)/);
                if (!m) continue;
                const pid = m[1];

                let solvedFlag = false;
                const cls = a.className || '';
                if (/solved|accepted|ok|green/i.test(cls)) solvedFlag = true;
                if (!solvedFlag && /\u2713|\u2714|✓|✔/.test(a.innerText)) solvedFlag = true;
                if (!solvedFlag) {
                    try {
                        if (isGreen(a)) solvedFlag = true;
                    } catch (e) {}
                }
                if (!solvedFlag) {
                    let el = a.parentElement;
                    for (let i = 0; i < 3 && el; ++i) {
                        try {
                            if (el.innerText && /Accepted|Solved|OK/i.test(el.innerText)) {
                                solvedFlag = true;
                                break;
                            }
                        } catch (e) {}
                        el = el.parentElement;
                    }
                }

                if (solvedFlag) solved.push({
                    pid,
                    href: href.startsWith('http') ? href : ('https://cses.fi' + href),
                    text: a.innerText.trim()
                });
            }
            // dedupe by pid
            const out = {};
            for (const s of solved)
                if (!out[s.pid]) out[s.pid] = s;
            return Object.keys(out).map(k => out[k]);
        });

        console.log(`Detected ${solvedList.length} solved problems (heuristic).`);

        await fs.ensureDir(argv.out);

        let userPageCache = null;
        let userPageCachePidMap = {}; 

        const buildUserSubmissionsCache = async () => {
            console.log('Loading user submissions page to build fallback mapping...');
            const userUrl = `https://cses.fi/problemset/user/${argv.username}/`;
            await page.goto(userUrl, {
                waitUntil: 'networkidle2'
            });
            await sleep(page, 300);
            const map = await page.evaluate((myUser) => {
                const out = {};
                const rows = Array.from(document.querySelectorAll('tr'));
                for (const r of rows) {
                    const txt = r.innerText || '';
                    if (!txt.includes(myUser)) continue;
                    const pidMatch = txt.match(/\b(\d{2,6})\b/);
                    if (!pidMatch) continue;
                    const pid = pidMatch[1];
                    if (out[pid]) continue;
                    if (!/Accepted|OK|Correct/i.test(txt)) continue;
                    const a = r.querySelector('a[href*="/result/"]');
                    if (a) {
                        const href = a.getAttribute('href');
                        const full = href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/' + href);
                        out[pid] = full;
                    }
                }
                // fallback anchors:
                if (Object.keys(out).length === 0) {
                    const anchors = Array.from(document.querySelectorAll('a[href*="/result/"]'));
                    for (const a of anchors) {
                        const tr = (function(el) {
                            let cur = el;
                            while (cur) {
                                if (cur.tagName && cur.tagName.toLowerCase() === 'tr') return cur;
                                cur = cur.parentElement;
                            }
                            return null;
                        })(a);
                        const txt = tr ? (tr.innerText || '') : (a.parentElement ? (a.parentElement.innerText || '') : '');
                        if (!txt.includes(myUser)) continue;
                        if (!/Accepted|OK|Correct/i.test(txt)) continue;
                        const m = txt.match(/\b(\d{2,6})\b/);
                        if (!m) continue;
                        const pid = m[1];
                        const href = a.getAttribute('href');
                        out[pid] = href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/' + href);
                    }
                }
                return out;
            }, argv.username);

            userPageCache = true;
            userPageCachePidMap = map;
            console.log(`User page mapping built for ${Object.keys(map).length} problem(s) (first-page scan).`);
        };

        let savedCount = 0;

        // iterate each solved problem
        for (let i = 0; i < solvedList.length; ++i) {
            const s = solvedList[i];
            const pid = s.pid;
            const meta = problemMap[pid] || {
                section: 'Unknown',
                title: s.text || ('Problem_' + pid),
                href: s.href
            };
            const sectionName = safeName(meta.section);
            const problemTitle = safeName(meta.title || ('Problem_' + pid));
            const taskUrl = absoluteUrl(meta.href || s.href);

            console.log(`\n[${i+1}/${solvedList.length}] Problem ${pid} - "${problemTitle}" (section: "${sectionName}")`);
            try {
                await page.goto(taskUrl, {
                    waitUntil: 'networkidle2'
                });
                await sleep(page, 300);

                let problemText = await page.evaluate(() => {
                    const selectors = ['#content', '.content', 'article', 'main', '.problem'];
                    function cleanTextFromElement(el) {
                        if (!el) return '';
                        const clone = el.cloneNode(true);
                        // remove scripts, styles, links, noscript
                        const removes = clone.querySelectorAll('script, style, link, noscript');
                        removes.forEach(n => n.remove());
                        // remove hidden or display:none nodes
                        const all = Array.from(clone.querySelectorAll('*'));
                        all.forEach(node => {
                            try {
                                const cs = window.getComputedStyle(node);
                                if (!cs) return;
                                if (cs.display === 'none' || cs.visibility === 'hidden' || cs.opacity === '0') {
                                    node.remove();
                                }
                            } catch (e) {
                                // ignore
                            }
                        });
                        // get visible inner text
                        return (clone.innerText || '').replace(/\r/g, '').trim();
                    }
                    for (const sel of selectors) {
                        try {
                            const el = document.querySelector(sel);
                            if (el) {
                                const t = cleanTextFromElement(el);
                                if (t && t.length > 0) return t;
                            }
                        } catch (e) {}
                    }
                    // fallback: find element that looks like a problem by keywords
                    const candidates = Array.from(document.querySelectorAll('div, section, article, main'));
                    for (const d of candidates) {
                        try {
                            const txt = d.innerText || '';
                            if (txt.length > 40 && (txt.includes('Input') || txt.includes('Output') || txt.includes('Sample') || /Constraints/i.test(txt) || /\bInput\b/.test(txt))) {
                                const t = cleanTextFromElement(d);
                                if (t && t.length > 0) return t;
                            }
                        } catch (e) {}
                    }
                    // final fallback: whole body text
                    return (document.body && document.body.innerText) ? document.body.innerText.replace(/\r/g, '').trim() : '';
                });
                // normalize whitespace a bit: collapse multiple blank lines
                if (problemText) {
                    problemText = problemText.replace(/\n{3,}/g, '\n\n').trim();
                } else {
                    problemText = '';
                }

                // 1) try to find direct /result/<id>/ links on the task page
                const candidateResultLinks = await page.evaluate((myUser) => {
                    const matches = [];
                    const anchors = Array.from(document.querySelectorAll('a'));
                    for (const a of anchors) {
                        const href = a.getAttribute('href') || '';
                        const m = href.match(/\/result\/(\d+)\/?/);
                        if (m) {
                            const hrefFull = href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/' + href);
                            let ancestorText = '';
                            let el = a.parentElement;
                            let depth = 0;
                            while (el && depth < 6) {
                                if (el.innerText) ancestorText += ' ' + el.innerText;
                                el = el.parentElement;
                                depth++;
                            }
                            matches.push({
                                href: hrefFull,
                                anchorText: a.innerText || '',
                                ancestorText: ancestorText.trim()
                            });
                        }
                    }
                    return matches;
                }, argv.username);

                let chosenResultLink = null;

                if (candidateResultLinks && candidateResultLinks.length > 0) {
                    for (const c of candidateResultLinks) {
                        if ((c.ancestorText || '').includes(argv.username) && /Accepted|OK|Correct/i.test(c.ancestorText || '')) {
                            chosenResultLink = c.href;
                            break;
                        }
                    }
                    if (!chosenResultLink) {
                        for (const c of candidateResultLinks) {
                            if (/Accepted|OK|Correct/i.test(c.anchorText || '') || /Accepted|OK|Correct/i.test(c.ancestorText || '')) {
                                chosenResultLink = c.href;
                                break;
                            }
                        }
                    }
                    if (!chosenResultLink) chosenResultLink = candidateResultLinks[0].href;
                }

                // 2) fallback to user submissions page
                if (!chosenResultLink) {
                    if (!userPageCache) await buildUserSubmissionsCache();
                    if (userPageCachePidMap[pid]) {
                        chosenResultLink = userPageCachePidMap[pid];
                        console.log('  Fallback: found result link from user submissions page cache.');
                    } else {
                        console.log('  No result on task page; scanning user submissions page for this problem...');
                        await page.goto(`https://cses.fi/problemset/user/${argv.username}/`, {
                            waitUntil: 'networkidle2'
                        });
                        await sleep(page, 300);
                        const foundLink = await page.evaluate((pid, myUser) => {
                            const rows = Array.from(document.querySelectorAll('tr'));
                            for (const r of rows) {
                                const txt = r.innerText || '';
                                if (!txt.includes(myUser)) continue;
                                if (!/Accepted|OK|Correct/i.test(txt)) continue;
                                if (!txt.includes(pid)) continue;
                                const a = r.querySelector('a[href*="/result/"]');
                                if (a) {
                                    const href = a.getAttribute('href');
                                    return href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/' + href);
                                }
                            }
                            const anchors = Array.from(document.querySelectorAll('a[href*="/result/"]'));
                            for (const a of anchors) {
                                const tr = (function(el) {
                                    let cur = el;
                                    while (cur) {
                                        if (cur.tagName && cur.tagName.toLowerCase() === 'tr') return cur;
                                        cur = cur.parentElement;
                                    }
                                    return null;
                                })(a);
                                const txt = tr ? (tr.innerText || '') : (a.parentElement ? (a.parentElement.innerText || '') : '');
                                if (!txt.includes(myUser)) continue;
                                if (!/Accepted|OK|Correct/i.test(txt)) continue;
                                if (!txt.includes(pid)) continue;
                                const href = a.getAttribute('href');
                                return href.startsWith('http') ? href : (href.startsWith('/') ? 'https://cses.fi' + href : 'https://cses.fi/' + href);
                            }
                            return null;
                        }, pid, argv.username);

                        if (foundLink) {
                            chosenResultLink = foundLink;
                            userPageCachePidMap[pid] = foundLink;
                        }
                        await page.goto(taskUrl, {
                            waitUntil: 'networkidle2'
                        });
                        await sleep(page, 200);
                    }
                }

                if (!chosenResultLink) {
                    console.warn('  Could not find any result link for this problem (on task page or user submissions). Skipping.');
                    await sleep(page, argv.delay);
                    continue;
                }

                console.log('  Opening result page:', chosenResultLink);
                await page.goto(chosenResultLink, {
                    waitUntil: 'networkidle2'
                });
                await sleep(page, 200);

                const resultData = await page.evaluate((myUser) => {
                    const data = {
                        code: null,
                        lang: null,
                        verdictText: null,
                        userFound: false,
                        pageTitle: document.title || ''
                    };
                    data.verdictText = document.body.innerText || '';
                    const pres = Array.from(document.querySelectorAll('pre'));
                    if (pres.length > 0) {
                        let big = pres[0];
                        for (const p of pres) {
                            if ((p.innerText || '').length > (big.innerText || '').length) big = p;
                        }
                        data.code = big.innerText;
                    } else {
                        const codes = Array.from(document.querySelectorAll('code'));
                        if (codes.length > 0) {
                            let big = codes[0];
                            for (const c of codes) {
                                if ((c.innerText || '').length > (big.innerText || '').length) big = c;
                            }
                            data.code = big.innerText;
                        }
                    }
                    const body = document.body.innerText || '';
                    const m = body.match(/Language:\s*([A-Za-z0-9\+\#\s\.\-]+)/);
                    if (m) data.lang = m[1].trim();
                    if (body.includes(myUser)) data.userFound = true;
                    return data;
                }, argv.username);

                if (!resultData.userFound) {
                    console.warn('  Warning: username not found on result page — continuing but double-check if this is not your result.');
                }
                if (!isAcceptedText(resultData.verdictText)) {
                    console.warn('  Warning: result page does not clearly show Accepted verdict. Skipping saving this result.');
                    await sleep(page, argv.delay);
                    continue;
                }
                if (!resultData.code || resultData.code.trim().length < 3) {
                    console.warn('  No code found on result page. Skipping.');
                    await sleep(page, argv.delay);
                    continue;
                }

                // Save file (now include problem TEXT above the solution inside a comment)
                const ext = guessExtFromLang(resultData.lang || '');
                const sectionDir = path.join(argv.out, safeName(sectionName));
                await fs.ensureDir(sectionDir);
                const filenameBase = `${problemTitle.replace(/\s+/g, '_')}_${pid}`;
                let filename = `${filenameBase}${ext}`;
                let fp = path.join(sectionDir, filename);
                if (await fs.pathExists(fp)) {
                    const ts = Date.now();
                    filename = `${filenameBase}_${ts}${ext}`;
                    fp = path.join(sectionDir, filename);
                }

                // prepare final content: comment header + problem TEXT (safely escaped) + solution code
                const safeProblemText = (problemText || '').replace(/\*\//g, '*\\/');
                const finalContent = `/* problem statement text */\n/*\n${safeProblemText}\n*/\n${resultData.code}`;

                await fs.writeFile(fp, finalContent, 'utf8');
                console.log(`  Saved AC -> ${fp} (lang: ${resultData.lang || 'unknown'})`);
                savedCount += 1;

                await sleep(page, argv.delay);
            } catch (err) {
                console.warn('  Error processing problem', pid, ':', err && err.message ? err.message : err);
            }
        }

        console.log(`\nFinished. Saved ${savedCount} files under: ${path.resolve(argv.out)}`);
    } catch (err) {
        console.error('Fatal error:', err && err.message ? err.message : err);
    } finally {
        try {
            await browser.close();
        } catch (e) {}
    }
})();
