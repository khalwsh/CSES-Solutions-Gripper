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
const int N = 3e5 + 10;
int n;
int s[N];
vector<int>adj[N];
ll sum = 0;
ll ans[N];
void dfs1(int u , int p , int cur = 0) {
    s[u] = 1;
    sum += cur;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs1(v , u , cur + 1);
        s[u] += s[v];
    }
}
void dfs2(int u , int p) {
    ans[u] = sum;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        int subtree = s[v];
        int out = n - s[v];
        sum += out - subtree;
        dfs2(v , u);
        sum -= out - subtree;
    }
}
int main() {
    PRE();
    cin>>n;
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(0 , -1);
    dfs2(0 , -1);
    for (int i = 0;i < n;i++)
        cout<<ans[i]<<" ";
}