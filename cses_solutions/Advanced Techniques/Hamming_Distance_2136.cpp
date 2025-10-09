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
 
int main() {
    PRE();
    int n, k;
    cin >> n >> k;
    int res = k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (auto &val: s) {
            v[i] <<= 1;
            v[i] |= (val - '0');
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            res = min(res, __builtin_popcount(v[i] ^ v[j]));
        }
    }
    cout << res << '\n';
}