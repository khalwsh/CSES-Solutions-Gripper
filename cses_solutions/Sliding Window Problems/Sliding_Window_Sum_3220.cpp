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
    int n , k;
    ll x , a , b , c;
    cin >> n >> k >> x >> a >> b >> c;
    ll ans = 0;
    vector<ll>v(n);
    v[0] = x;
    for (int i = 1;i < n;i++) {
        v[i] = (v[i - 1] * a + b) % c;
    }
    ll sum = 0;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            ans ^= sum;
            sum -= v[i - k];
        }
        sum += v[i];
    }
    ans ^= sum;
    cout << ans << '\n';
}