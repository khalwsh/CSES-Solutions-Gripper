#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("popcnt")
 
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
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i] = s;
    }
    for (int ch = 0; ch < m; ch++) {
        vector<bitset<3000> > bs(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bs[i][j] = (v[i][j] - 'A') == ch;
            }
        }
        bool ok = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((bs[i] & bs[j]).count() >= 2) {
                    ok = true;
                    break;
                }
            }
            if (ok)break;
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}