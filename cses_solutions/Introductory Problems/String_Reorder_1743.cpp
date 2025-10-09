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
bool canArrange(const array<int,26> &freq, int remaining) {
    int maxFreq = *max_element(freq.begin(), freq.end());
    return maxFreq <= (remaining + 1) / 2;
}
int main() {
    PRE();
    string s;
    cin >> s;
    int n = s.size();
    array<int,26> freq{};
    for (char c : s) freq[c - 'A']++;
 
    if (!canArrange(freq, n)) {
        cout << -1 << "\n";
        return 0;
    }
 
    string result;
    result.reserve(n);
    char prev = '\0';
 
    for (int pos = 0; pos < n; pos++) {
        for (int c = 0; c < 26; c++) {
            if (freq[c] == 0) continue;
            if (prev == 'A' + c) continue;
 
            freq[c]--;
            if (canArrange(freq, n - pos - 1)) {
                result.push_back('A' + c);
                prev = 'A' + c;
                break;
            }
            // Undo and try next
            freq[c]++;
        }
    }
 
    cout << result << "\n";
}