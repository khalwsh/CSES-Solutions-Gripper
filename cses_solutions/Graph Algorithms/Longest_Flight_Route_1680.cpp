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
const int N = 3e5 + 1;
vector<int>adj[N];
int in[N] , dp[N] , nxt[N];
int main() {
    PRE();
    int m;
    int n;cin>>n>>m;
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        in[v]++;
    }
    vector<int>topo;
    queue<int>q;
    for (int i = 0;i < n;i++) {
        if (!in[i]) {
            q.push(i);
        }
    }
    while (q.size()) {
        int node = q.front();q.pop();
        topo.push_back(node);
        for (auto &val:adj[node]) {
            if (--in[val] == 0) {
                q.push(val);
            }
        }
    }
    if (topo.size() != n) {
        cout<<"IMPOSSIBLE";
        exit(0);
    }
    for (auto &v : dp) v = -1e9;
    memset(nxt , -1 , sizeof nxt);
    dp[n - 1] = 0;
    for (int i = topo.size() - 1;i >= 0;i--) {
        for (auto &v : adj[topo[i]]) {
            if (dp[v] + 1 > dp[topo[i]]){
                dp[topo[i]] = 1 + dp[v];
                nxt[topo[i]] = v;
            }
        }
    }
    if (dp[0] < 0) {
        cout<<"IMPOSSIBLE";
        exit(0);
    }
    vector<int>path;
    int u = 0;
    do {
        path.push_back(u + 1);
        u = nxt[u];
    }while (~u);
    assert(dp[0] + 1 == path.size());
    cout<<dp[0] + 1<<'\n';
    for (auto &v : path)
        cout<<v<<" ";
}