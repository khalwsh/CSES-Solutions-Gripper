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
 
ll f(ll n,ll k){
    if(n == 1) return 1;
    if(k <= (n + 1) / 2) {
        if(2 * k > n) return (2 * k) % n;
        else return 2 * k;
    }
    ll temp = f(n / 2,k - (n + 1) / 2);
    if(n % 2 == 1) return 2 * temp + 1;
    return 2 * temp - 1;
}
 
int main() {
    PRE();
    int q; cin >> q;
    while (q--) {
        int n , k; cin >> n >> k;
        cout << f(n , k) << '\n';
    }
}