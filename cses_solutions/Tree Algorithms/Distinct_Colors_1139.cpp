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
const int N = 2e5 + 10;
int v[N] , ans[N] , sz[N];
vector<int>adj[N];
set<int>colors[N];
 
void dfs(int u , int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs(v , u);
        sz[u] += sz[v];
    }
    int bg = -1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        if (bg == -1 || sz[bg] < sz[v]) bg = v;
    }
    if (bg != -1)
        swap(colors[u] , colors[bg]);
    colors[u].insert(v[u]);
    for (auto &v : adj[u]) {
        if (v == p || v == bg)continue;
        for (auto &val : colors[v]) colors[u].insert(val);
    }
    ans[u] = colors[u].size();
}
int main() {
    PRE();
    int n;cin>>n;
    for (int i = 0;i < n;i++) cin >> v[i];
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    dfs(0 , -1);
    for (int i = 0;i < n;i++) {
        cout<<ans[i]<<" ";
    }
}