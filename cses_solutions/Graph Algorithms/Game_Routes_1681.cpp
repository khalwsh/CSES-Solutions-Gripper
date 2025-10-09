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
int in[N] , dp[N];
const int mod = 1e9 + 7;
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
    dp[n - 1] = 1;
    for (int i = topo.size() - 1;i >= 0;i--) {
        for (auto &v : adj[topo[i]]) {
            dp[topo[i]] += dp[v];
            dp[topo[i]] %= mod;
        }
    }
    cout<<dp[0]<<'\n';
}