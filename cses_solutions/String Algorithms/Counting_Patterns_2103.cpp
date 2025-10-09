#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
const int N = 5e5 + 10;
int ans[N];
 
struct AhoCorasick {
    /// Modify these values based on input alphabet
    /// alpha: size of alphabet (26 for lowercase letters)
    /// first: first character of alphabet ('a' for lowercase letters)
    enum { alpha = 26, first = 'a' };
 
    struct Node {
        int nxt[alpha]; /// Next state transition for each character
        int suflink = 0; /// Suffix link points to longest proper suffix
        int start = -1; /// Start index of pattern in original array
        int end = -1; /// Index in backup of longest matched suffix pattern
        int nmatches = 0; ///Count of matched strings ending at this node
        int lvl = 0;
 
        Node(int v) {
            memset(nxt, v, sizeof nxt);
        }
    };
 
    vector<int> IDs;
    vector<Node> v; /// Stores all nodes of the trie
    vector<int> backup;
    /// Stores pattern indices with longest matching suffixes
       /// Returns -1 if no match exists
       /// Note: All patterns must be distinct when using backup
 
    /// Inserts a pattern into the automaton
    /// Time: O(|s|) where |s| is pattern length
    void insert(string &s, int id) {
        int node = 0;
        int clvl = 0;
        for (auto &c: s) {
            int &m = v[node].nxt[c - first];
 
            ++clvl;
            if (m == -1) {
                node = m = v.size();
                v.emplace_back(-1);
                v.back().lvl = clvl;
            } else node = m;
        }
        if (v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end);
        v[node].end = id;
        v[node].nmatches++;
        IDs.emplace_back(node);
    }
 
    /// Builds Aho-Corasick automaton from patterns
    /// Time: O(26N) where N = sum of all pattern lengths
    /// - Creates suffix links
    /// - Allows duplicate patterns
    /// - For large alphabets, split symbols into chunks with sentinel bits
    AhoCorasick(vector<string> &pat) : v(1, -1) {
        for (int i = 0; i < pat.size(); ++i)
            insert(pat[i], i);
        v[0].suflink = v.size();
        v.emplace_back(0);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            int prv = v[node].suflink;
 
            for (int i = 0; i < alpha; ++i) {
                int &x = v[node].nxt[i], y = v[prv].nxt[i];
                if (x == -1) x = y;
                else {
                    v[x].suflink = y;
                    (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                    v[x].nmatches += v[y].nmatches;
                    q.push(x);
                }
            }
        }
    }
 
    // Returns index of longest word ending at each position, or -1 if none
    // Time: O(|word|) where |word| is text length
    vector<int> find(string &word) {
        int node = 0;
        vector<int> res;
        for (auto &c: word) {
            node = v[node].nxt[c - first];
            res.push_back(v[node].end);
        }
        return res;
    }
 
    // Propagates values up the suffix links in decreasing depth order
    // Useful for transferring match info (e.g., pattern IDs, frequencies, counts, etc.)
    // Nodes are processed deepest to shallowest to ensure correctness
    // Time: O(total number of nodes)
    void propagate() {
        int N = v.size() - 1; // exclude dummy node
        int ind[N];
        iota(ind, ind + N, 0); // fill with 0..N-1
        sort(ind, ind + N, [&](int x, int y) {
            return v[x].lvl > v[y].lvl; // sort by depth descending
        });
        for (int i = 0; i < N; ++i) {
            int x = ind[i];
            int link = v[x].suflink;
            // TODO: propagate information from node x to its suffix link
            ans[link] += ans[x];
        }
    }
 
    void solve(string &text) {
        int cur = 0;
        for (auto &val: text) {
            cur = v[cur].nxt[val - 'a'];
            if (v[cur].nmatches) ans[cur]++;
        }
    }
};
 
int main() {
    PRE();
    string text;
    cin >> text;
    int n;
    cin >> n;
    vector<string> pat;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        pat.emplace_back(x);
    }
    AhoCorasick aho(pat);
    aho.solve(text);
    aho.propagate();
    for (int i = 0; i < n; i++) {
        cout << ans[aho.IDs[i]] << "\n";
    }
}