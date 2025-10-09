#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
struct WindowFreq {
    map<int, int> freq;
    map<int, multiset<int>> fte;
 
    void add(int x) {
        int old = freq[x];
        if (old > 0) {
            auto it = fte.find(old);
            if (it != fte.end()) {
                auto mit = it->second.find(x);
                if (mit != it->second.end()) it->second.erase(mit);
                if (it->second.empty()) fte.erase(it);
            }
        }
        freq[x]++;
        fte[freq[x]].insert(x);
    }
 
    void remove(int x) {
        int old = freq[x];
        if (old == 0) return;
 
        auto it = fte.find(old);
        if (it != fte.end()) {
            auto mit = it->second.find(x);
            if (mit != it->second.end()) it->second.erase(mit);
            if (it->second.empty()) fte.erase(it);
        }
 
        freq[x]--;
        if (freq[x] == 0) {
            freq.erase(x);
            return;
        }
        fte[freq[x]].insert(x);
    }
 
    int getBest() const {
        if (fte.empty()) return -1;
        auto it = fte.rbegin();
        return *it->second.begin();
    }
 
    int uniqueCount() const {
        return (int)freq.size();
    }
};
 
int main() {
    PRE();
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
 
    WindowFreq wf;
 
    for (int i = 0; i < n; i++) {
        if (i >= k) {
            cout << wf.getBest() << ' ';
            wf.remove(v[i - k]);
        }
        wf.add(v[i]);
    }
    cout << wf.getBest() << ' ';
}