#include <bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
#include "dev/debug.hpp"
#else
#define debug(...) 8
#endif
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
 
#define all(x) (x).begin(), (x).end()
#define f(i, x, n) for (ll i = x; i < n; i++)
#define rf(i, x, n) for (ll i = x; i >= n; i--)
 
const ll mod = 1e9+7;
const ll mod2 = 998244353;
const ll N = 1e6+5;
 
void init(){
 
}
 
void solve(){
    ll n, k;
    cin >> n >> k;
 
    ll x, a, b, c;
    cin >> x >> a >> b >> c;
 
    vector<ll> p(n), s(n), v(n);
    p[0] = s[n - 1] = x;
    v[0] = x;
    f(i, 1, n) v[i] = (v[i - 1] * a + b) % c;
 
    ll ans = 0;
    if(k == 1){
        f(i, 0, n) ans ^= v[i];
        cout << ans << "\n";
        return;
    }
 
    f(i, 1, n){
        p[i] = (i % k == 0 ? v[i] : p[i - 1] | v[i]);
    }
 
    rf(i, n - 2, 0){
        s[i] = (i % k == k - 1 ? v[i] : s[i + 1] | v[i]);
    }
 
 
    f(i, k - 1, n){
        if(i % k == k - 1){
            ans ^= p[i];
        }else{
            ans ^= (s[i - k + 1] | p[i]);
        }
    }
 
    cout << ans << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
    // #ifndef ONLINE_JUDGE
    //   freopen("input.txt", "r", stdin);
    //   freopen("output.txt", "w", stdout);
    //   freopen("Error.txt", "w", stderr);
    // #endif
 
    init();
 
    ll t = 1;
    // cin >> t;
    for (ll T = 1; T <= t; T++) {
        // debug(T);
        solve();
    }
    return 0;
}