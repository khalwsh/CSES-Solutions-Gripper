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
    vector<ll>tree , lazy;
    void init(int x) {
        tree.resize(4 * x);
        lazy.resize(4 * x);
    }
    void prop(int node , int nl , int nr) {
        if (lazy[node]) {
            tree[node] = (nr - nl + 1) * lazy[node];
            if (nl != nr) {
                lazy[2 * node + 1] = lazy[node];
                lazy[2 * node + 2] = lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void upd(int node , int nl , int nr , int l , int r , ll nw_val) {
        prop(node , nl , nr);
        if (nl >= l && nr <= r) {
            lazy[node] = nw_val;
            prop(node , nl , nr);
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        upd(2 * node + 1 , nl , mid , l , r , nw_val);
        upd(2 * node + 2 , mid + 1 , nr , l ,r , nw_val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    ll query(int node , int nl , int nr , int l , int r) {
        prop(node , nl , nr);
        if (nl >= l && nr <= r) {
            return tree[node];
        }
        if (nl > r || nr < l) return 0;
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1 , nl , mid , l , r) + query(2 * node + 2 , mid + 1 , nr , l , r);
    }
}seg;
const int N = 2e5 + 1;
int n , q ;
ll values[N];
 
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
ll query_path(int u, int v) {
    ll res = 0;
    while (root[u] != root[v]) {
        if (depth[root[u]] < depth[root[v]]) swap(u, v);
        res += seg.query(0, 0, n - 1, pos[root[u]], pos[u]);
        u = parent[root[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += seg.query(0, 0, n - 1, pos[u], pos[v]);
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
            int u;cin>>u;
            u--;
            cout<<query_path(0 , u)<<'\n';
        }
    }
}