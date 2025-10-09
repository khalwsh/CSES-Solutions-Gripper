#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 1;
vector<vector<int>> adj , dag , comps;
int comp[N] , inStack[N] , lowLink[N] , dfn[N] , deg[N];
stack<int> st;
int ndfn;
void tarjan(int u){
    dfn[u] = lowLink[u] = ndfn++;
    inStack[u] = true;
    st.push(u);
    for(auto &v : adj[u]){
        if(dfn[v] == -1){
            tarjan(v);
            lowLink[u] = min(lowLink[u] , lowLink[v]);
        }else if(inStack[v]){
            lowLink[u] = min(lowLink[u] , dfn[v]);
        }
    }
    if(dfn[u] == lowLink[u]){
        // head of component
        int x = -1;
        comps.emplace_back(vector<int>());
        while(x != u){
            x = st.top(); st.pop(); inStack[x] = 0;
            comps.back().emplace_back(x);
            comp[x] = (int)comps.size() - 1;
        }
    }
}
void genDag(){
    dag.resize(comps.size());
    for(int u = 0 ; u < adj.size() ; u++){
        for(auto &v :adj[u]){
            if(comp[u] != comp[v]){
                dag[comp[u]].emplace_back(comp[v]);
                deg[comp[v]]++;
            }
        }
    }
}
void SCC(int n){
    ndfn = 0;
    comps.clear();
    for(int i=0;i<n;i++){
        dfn[i] = -1;
        lowLink[i] = inStack[i] = deg[i] = 0;
    }
    for(int i = 0 ; i < n ; i++)
        if(dfn[i] == -1) tarjan(i);
    genDag();
}
int n , m , qq;
bitset<N>dp[N];
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>qq;
    adj.resize(n);
    for(int i = 0;i < m;i++) {
        int u , v;cin>>u>>v; u-- , v--;
        adj[u].emplace_back(v);
    }
    SCC(n);
    queue<int>q;
    for(int i = 0;i < comps.size();i++) {
        if(!deg[i])q.push(i);
    }
    vector<int>topo;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        topo.emplace_back(node);
        for(auto &val:dag[node]) {
            if(!--deg[val])q.push(val);
        }
    }
    for(int i = topo.size() - 1;i >= 0;i--) {
        dp[topo[i]][topo[i]] = true;
        for(auto &val:dag[topo[i]]) {
            dp[topo[i]] |= dp[val];
        }
    }
    while(qq--) {
        int u , v;cin>>u>>v;
        u-- , v--;
        cout<<(dp[comp[u]][comp[v]] ? "YES":"NO")<<"\n";
    }
}