#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF_LL = (ll)4e18;
 
struct LiChaoMax {
    struct Line { ll m, b; };
    int n;
    vector<ll> xs;
    vector<Line> st;
 
    LiChaoMax(const vector<ll>& coords) {
        xs = coords;
        n = xs.size();
        st.assign(4 * n, {0, -INF_LL});
    }
 
    ll eval(const Line& ln, ll x) const {
        return ln.m * x + ln.b;
    }
 
    void add_line(ll m, ll b) {
        insert(1, 0, n, {m, b});
    }
 
    void add_segment(ll m, ll b, ll xl, ll xr) {
        int L = lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (L < R) insert_seg(1, 0, n, {m, b}, L, R);
    }
 
    ll query(ll xq) const {
        int idx = lower_bound(xs.begin(), xs.end(), xq) - xs.begin();
        return query_point(1, 0, n, xq, idx);
    }
 
private:
    void insert(int p, int l, int r, Line ln) {
        int m = (l + r) >> 1;
        ll xl = xs[l], xm = xs[m], xr = xs[r-1];
        Line& cur = st[p];
        if (eval(ln, xm) > eval(cur, xm)) swap(cur, ln);
        if (r - l == 1) return;
        if (eval(ln, xl) > eval(cur, xl))
            insert(p<<1, l, m, ln);
        else if (eval(ln, xr) > eval(cur, xr))
            insert(p<<1|1, m, r, ln);
    }
 
    void insert_seg(int p, int l, int r, Line ln, int ql, int qr) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            insert(p, l, r, ln);
            return;
        }
        int m = (l + r) >> 1;
        insert_seg(p<<1, l, m, ln, ql, qr);
        insert_seg(p<<1|1, m, r, ln, ql, qr);
    }
 
    ll query_point(int p, int l, int r, ll xq, int idx) const {
        ll res = eval(st[p], xq);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (idx < m)
            res = max(res, query_point(p<<1, l, m, xq, idx));
        else
            res = max(res, query_point(p<<1|1, m, r, xq, idx));
        return res;
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> segs(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segs[i] = {x1, y1, x2, y2};
    }
    vector<ll> xs(m+1);
    for (int x = 0; x <= m; x++) xs[x] = x;
 
    LiChaoMax lichao(xs);
    for (auto& seg : segs) {
        ll x1, y1, x2, y2;
        tie(x1, y1, x2, y2) = seg;
        ll dx = x2 - x1;
        ll dy = y2 - y1;
        ll a = dy / dx;
        ll b = y1 - a * x1;
        lichao.add_segment(a, b, x1, x2 + 1);
    }
 
    for (int x = 0; x <= m; x++) {
        ll ans = lichao.query(x);
        if (ans < -INF_LL/2) cout << -1;
        else cout << ans;
        if (x < m) cout << ' ';
    }
    cout << '\n';
    return 0;
}