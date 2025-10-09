#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 1;
int sub[N] , add[N];
vector<int>adj[N];
int up[20][N];
int depth[N];
void dfs(int node , int par) {
    depth[node] = (par == -1 ? 0 : depth[par] + 1);
    for(auto &val:adj[node]) {
        if(val == par)continue;
        up[0][val] = node;
        dfs(val , node);
    }
}
int pref[N];
void dfs2(int node , int par ) {
    for(auto &val:adj[node]) {
        if(val == par)continue;
        dfs2(val , node);
        pref[node] += pref[val];
    }
}
int main() {
    int n , m;cin>>n>>m;
    for(int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , -1);
    for(int i = 1;i < 20;i++) {
        for(int j = 0;j < n;j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    auto walk = [&](int u , int kth)->int {
        for(int i = 0;i < 20;i++) {
            if(kth & (1<<i))u = up[i][u];
        }
        return u;
    };
    auto lca = [&](int u , int v)->int {
        if(depth[u] > depth[v])swap(u , v);
        v = walk(v , depth[v] - depth[u]);
        if(u == v)return u;
        for(int i = 19; i >= 0;i--) {
            if(up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    };
    for(int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        if(depth[v] < depth[u])swap(u  , v);
        int l = lca(u , v);
        pref[u]++ , pref[v]++;
        pref[l]-- ;
        if(l != 0) pref[up[0][l]]--;
    }
    dfs2(0 , -1 );
    for(int i = 0;i < n;i++)cout<<pref[i]<<" ";
}