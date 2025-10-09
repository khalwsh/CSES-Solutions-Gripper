#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
const int N = 2e5 + 10;
vector<int>adj[N];
int centriod = 0;
int siz[N];
void dfs1(int node , int par) {
    siz[node] = 1;
    for(auto &val:adj[node]) {
        if(val == par)continue;
        dfs1(val , node);
        siz[node] += siz[val];
    }
}
int dfs2(int node , int par) {
    for(auto &val:adj[node]) {
        if(val == par)continue;
        if(siz[val] > n / 2) {
            return dfs2(val , node);
        }
    }
    return node;
}
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i = 1;i < n;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(0 , -1);
    centriod = dfs2(0 , -1);
    cout<<centriod + 1<<'\n';
}