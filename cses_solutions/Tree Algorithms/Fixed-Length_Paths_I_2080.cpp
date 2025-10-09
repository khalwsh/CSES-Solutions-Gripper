#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 2e5 + 10;
vector<int>adj[N];
int n , k , sz[N];
ll res = 0;
bool removed[N];
 
int cnt[N];
 
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p || removed[v])continue;
        sz[u] += dfs_sz(v , u);
    }
    return sz[u];
}
 
int dfs_centroid(int u, int p, int s) {
    for (auto &v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > s) return dfs_centroid(v , u , s);
    }
    return u;
}
 
void dfs_add(int u , int p , int depth , int delta) {
    cnt[depth] += delta;
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_add(v , u , depth + 1 , delta);
    }
}
 
void dfs_ans(int u , int p , int depth) {
    if (depth <= k) res += cnt[k - depth];
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_ans(v , u , depth + 1);
    }
}
 
void decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
 
    // 1) count all paths passing through 'centroid'
    cnt[0] = 1;
    for (int v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_ans(v, centroid, 1);
        dfs_add(v, centroid, 1, +1);
    }
 
    // 2) roll back the counts
    for (int i = 0;i <= comp_sz;i++) cnt[i] = 0;
 
    // 3) remove the centroid and recurse in each resulting component
    removed[centroid] = true;
    for (int v : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}
 
 
int main() {
    PRE();
    cin >> n >> k;
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    decompose(0);
    cout<<res<<'\n';
}