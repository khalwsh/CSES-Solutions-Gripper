# CSES Auto Downloader

A Node.js script that automatically logs into your **CSES** account, navigates through all problems in the **Problem Set**, and downloads your **Accepted (AC)** solutions into organized folders by section and problem name.

---

## 🚀 Features
- Automatically logs in to your CSES account using Puppeteer.
- Navigates through the CSES problem set.
- Detects which problems you’ve solved (green ones).
- Opens your latest accepted submission for each solved problem.
- Downloads and saves your AC solution into a structured directory format.

**Example Folder Structure:**
```
cses_solutions/
│
├── Introductory Problems/
│   ├── Weird Algorithm.cpp
│   ├── Missing Number.cpp
│   └── Repetitions.cpp
│
├── Sorting and Searching/
│   ├── Distinct Numbers.cpp
│   ├── Apartments.cpp
│   └── Ferris Wheel.cpp
│
└── Graph Algorithms/
    ├── Counting Rooms.cpp
    └── Labyrinth.cpp
```

---

## ⚙️ Installation

### 1. Clone the repository
```bash
git clone https://github.com/khalwsh/CSES-Solutions-Grapper.git
cd CSES-Solutions-Grapper
```

### 2. Install dependencies
## 🧩 Dependencies
- [Node.js](https://nodejs.org/) >= 18.0.0
- [Puppeteer](https://pptr.dev/)
- [dotenv](https://www.npmjs.com/package/dotenv)
- [fs-extra](https://www.npmjs.com/package/fs-extra)

Install them via:
```bash
npm install puppeteer dotenv fs-extra
```

## ▶️ Usage

### Run the script
```bash
node CSES-scrapper.js --username YOUR_USERNAME --password YOUR_PASSWORD --out ./cses_solutions --headless true
```

The script will:
1. Launch a headless browser.
2. Log into CSES.
3. Visit all problems in the problem set.
4. Identify solved problems (green).
5. Visit each problem’s solution page.
6. Save the AC solution code into the correct folder.

---


## 🧠 Notes
- Avoid running too quickly (CSES may block your requests).
- Default headless mode is `true`, you can set it to `false` in the script to debug visually.
- The script skips unsolved problems automatically.
