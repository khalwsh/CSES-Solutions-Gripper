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
const int N = 3e5 + 1;
vector<int>adj[N];
int f[N] , g[N]; // f[i] : maximum number of nodes in the sub tree of i including i
                 // g[i] : maximum number of nodes in the sub tree of i not including i
void dfs(int u , int p) {
    // cout<<u<<endl;
    for (auto &v : adj[u]) {
        if (v != p) dfs(v , u);
    }
    for (auto &v : adj[u]) {
        if (v != p) {
            g[u] += max(f[v] , g[v]);
        }
    }
    for (auto &v : adj[u]) {
        if (v != p) {
            f[u] = max(f[u] , g[v] + 1 + g[u] - max(f[v] , g[v]));
        }
    }
}
int main() {
    PRE();
    int n;cin>>n;
    for (int i = 1;i < n;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , -1);
    cout<<max(f[0] , g[0]);
}