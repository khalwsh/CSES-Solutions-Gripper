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
 
const int mod = 1e9 + 7;
 
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    ll n;
    cin >> n;
    if (n & 1) {
        ll res = binpow(2, n * n) + 2 * (binpow(2, (n - 1) / 2 * (n + 1) / 2) * 2 + binpow(2, n * n / 2));
        res %= mod;
        cout << res * binpow(4, mod - 2) % mod << '\n';
    } else {
        ll res = binpow(2, n * n) + binpow(2, n * n / 4) * 2 + binpow(2, n * n / 2);
        res %= mod;
        cout << res * binpow(4, mod - 2) % mod << '\n';
    }
}