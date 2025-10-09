#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
struct SegmentTree {
    vector<int> tree;   // values
    vector<int> lazy;   // pending range-assignment tags
    int n = 0;          // original array size
    int base = 1;       // first leaf index (power of two ≥ n)
    int height = 0;     // ⌈log2(base)⌉
 
    /*–––– helpers (purely internal) ––––*/
    inline void build_height() {
        height = 0;
        while ((1 << height) < base) ++height;
    }
    inline void apply(int idx, int val) {
        tree[idx] = val;
        if (idx < base) lazy[idx] = val;
    }
    inline void push(int idx) {
        if (lazy[idx]) {
            apply(idx << 1,     lazy[idx]);
            apply(idx << 1 | 1, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    inline void push_path(int idx) {             // propagate root → leaf
        for (int h = height; h; --h)
            push(idx >> h);
    }
    inline void pull(int idx) {                  // recompute ancestors
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = lazy[idx] ? lazy[idx]
                                   : max(tree[idx << 1], tree[idx << 1 | 1]);
        }
    }
 
    /*–––– public API ––––*/
    void init(int x) {
        n = x;
        base = 1;
        while (base < n) base <<= 1;
        build_height();
        tree.assign(base << 1, 0);
        lazy.assign(base,      0);
    }
 
    // kept only for signature compatibility – internal push() is used instead
    void prop(int, int, int) {}
 
    void upd(int /*node*/, int /*nl*/, int /*nr*/,
             int l, int r, int nw_val) {
        int L = l + base, R = r + base;
        push_path(L);
        push_path(R);
 
        int l0 = L, r0 = R;                     // remember ends for pull()
        while (L <= R) {
            if (L & 1)  apply(L++, nw_val);
            if (!(R & 1)) apply(R--, nw_val);
            L >>= 1; R >>= 1;
        }
        pull(l0);
        pull(r0);
    }
 
    int query(int /*node*/, int /*nl*/, int /*nr*/,
              int l, int r) {
        int L = l + base, R = r + base;
        push_path(L);
        push_path(R);
 
        int ans = 0;
        while (L <= R) {
            if (L & 1)  ans = max(ans, tree[L++]);
            if (!(R & 1)) ans = max(ans, tree[R--]);
            L >>= 1; R >>= 1;
        }
        return ans;
    }
} seg;
 
const int N = 2e5 + 1;
int n , q ;
int values[N];
 
vector<int>adj[N];
int depth[N] , root[N] , pos[N] , heavy[N] , sz[N] , timer = 0 , parent[N];
void dfs_sz(int u , int p) {
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    parent[u] = p;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs_sz(v , u);
        sz[u] += sz[v];
    }
    heavy[u] = -1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
}
void decomose(int u , int p) {
    pos[u] = timer++;
    if (heavy[u] != -1) {
        root[heavy[u]] = root[u];
        decomose(heavy[u] , u);
    }
    for (auto &v : adj[u]) {
        if (v == p || heavy[u] == v)continue;
        root[v] = v;
        decomose(v , u);
    }
}
void upd_path(int u , int v , ll nw_val) {
    while (root[u] != root[v]) {
        if (depth[root[u]] < depth[root[v]]) swap(u, v);
        seg.upd(0, 0, n - 1, pos[root[u]], pos[u] , nw_val);
        u = parent[root[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    seg.upd(0, 0, n - 1, pos[u], pos[v] , nw_val);
}
int query_path(int u, int v) {
    int res = 0;
    while (root[u] != root[v]) {
        if (depth[root[u]] < depth[root[v]]) swap(u, v);
        res = max(seg.query(0, 0, n - 1, pos[root[u]], pos[u]) , res);
        u = parent[root[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res = max(seg.query(0, 0, n - 1, pos[u], pos[v]) , res);
    return res;
}
int main() {
    PRE();
    cin >>n >> q;
    seg.init(n);
    for (int i = 0;i < n;i++) cin>>values[i];
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    dfs_sz(0 , 0);
    decomose(0 , 0);
    for (int i = 0;i < n;i++) {
        seg.upd(0 , 0 , n - 1 , pos[i] , pos[i] , values[i]);
    }
    for (int i = 0;i < q;i++) {
        int type;cin>>type;
        if (type == 1) {
            int s , x;cin>>s>>x;
            s--;
            upd_path(s , s, x);
        }else {
            int u , v;cin>>u>>v;
            u--;
            v--;
            cout<<query_path(v , u)<<' ';
        }
    }
}