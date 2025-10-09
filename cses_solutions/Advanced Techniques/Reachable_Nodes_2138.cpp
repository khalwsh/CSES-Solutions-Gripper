#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 1;
bitset<N>adj[N];
vector<int>graph[N];
int in[N];
int n , m;
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        graph[u].emplace_back(v);
        in[v]++;
    }
    queue<int>nodes;
    for(int i = 0;i < n;i++) {
        if(!in[i])nodes.push(i);
    }
    vector<int>topo;
    topo.reserve(n);
    while(!nodes.empty()) {
        int node = nodes.front();
        nodes.pop();
        topo.emplace_back(node);
        for(auto &val:graph[node]) {
            if(!--in[val])nodes.push(val);
        }
    }
    // reverse(topo.begin() , topo.end())
    for(int i = n - 1;i >= 0;i--) {
        adj[topo[i]][topo[i]] = true;
        for(auto &val:graph[topo[i]]) {
            adj[topo[i]] |= adj[val];
        }
    }
    for(int i = 0;i < n;i++)cout<<adj[i].count()<<" ";
}