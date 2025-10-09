#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<> > {
    static const ll inf = LLONG_MAX;
    bool isMn = false;
 
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
 
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
 
    void add(ll k, ll m) {
        if (isMn) k = -k, m = -m;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
 
    ll query(ll x) {
        auto l = *lower_bound(x);
        return (isMn ? -1 : 1) * (l.k * x + l.m);
    }
};
 
int main() {
    PRE();
    LineContainer cht;
    cht.isMn = true;
    int n;
    cin >> n;
    ll x;
    cin >> x;
    vector<ll> f(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) cin >> f[i];
    for (int i = 1; i <= n; i++) cin >> s[i];
    s[0] = x;
    cht.add(x, 0);
    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = cht.query(f[i]);
        cht.add(s[i], dp[i]);
    }
    cout << dp[n] << '\n';
}