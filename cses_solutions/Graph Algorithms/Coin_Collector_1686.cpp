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
struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<ll> origWeight;
    vector<int> dag_in_degree;
    vector<int> dfn, lowLink, comp;
    vector<bool> inStack;
    stack<int> st;
    int timer;
 
    vector<vector<int>> components;
    vector<vector<int>> dag;
    vector<ll> compWeight;
 
    SCC(const vector<vector<int>>& graph, const vector<ll>& weight = {})
        : n(graph.size()), adj(graph) {
        if (weight.empty()) {
            origWeight.assign(n, 1);
        } else {
            if ((int)weight.size() != n)
                throw invalid_argument("Weight array size must match number of nodes");
            origWeight = weight;
        }
        dag_in_degree.resize(n);
        dfn.assign(n, -1);
        lowLink.assign(n, 0);
        comp.assign(n, -1);
        inStack.assign(n, false);
        timer = 0;
 
        for (int u = 0; u < n; u++) {
            if (dfn[u] == -1)
                tarjan(u);
        }
 
        buildDag();
 
        compWeight.assign(components.size(), 0);
        for (int u = 0; u < n; u++) {
            compWeight[ comp[u] ] += origWeight[u];
        }
    }
    const vector<vector<int>>& getSCCs() const {
        return components;
    }
    const vector<vector<int>>& getDAG() const {
        return dag;
    }
    const vector<ll>& getComponentWeights() const {
        return compWeight;
    }
    const vector<int>& getInDegree()const {
        return dag_in_degree;
    }
 
private:
    void tarjan(int u) {
        dfn[u] = lowLink[u] = timer++;
        inStack[u] = true;
        st.push(u);
 
        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                lowLink[u] = min(lowLink[u], lowLink[v]);
            } else if (inStack[v]) {
                lowLink[u] = min(lowLink[u], dfn[v]);
            }
        }
 
        if (lowLink[u] == dfn[u]) {
            components.emplace_back();
            while (true) {
                int x = st.top(); st.pop();
                inStack[x] = false;
                comp[x] = (int)components.size() - 1;
                components.back().push_back(x);
                if (x == u) break;
            }
        }
    }
 
    void buildDag() {
        int csz = components.size();
        dag.assign(csz, {});
        unordered_set<long long> seen;
 
        for (int u = 0; u < n; u++) {
            int cu = comp[u];
            for (int v : adj[u]) {
                int cv = comp[v];
                if (cu != cv) {
                    long long code = (long long)cu << 32 | (unsigned)cv;
                    if (seen.insert(code).second) {
                        dag_in_degree[cv]++;
                        dag[cu].push_back(cv);
                    }
                }
            }
        }
    }
};
int main() {
    PRE();
    int n , m;
    cin>>n>>m;
    vector<ll>weights(n);
    for (int i = 0;i < n;i++) {
        cin>>weights[i];
    }
    vector<vector<int>>graph(n);
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        graph[u].emplace_back(v);
    }
    SCC scc(graph , weights);
    auto dag = scc.getDAG();
    auto compressedWeights = scc.getComponentWeights();
    auto in = scc.getInDegree();
    vector<int>topo;
    queue<int>q;
    for (int i = 0;i < dag.size();i++) {
        // cout<<i<<" "<<weights[i]<<endl;
        if (in[i] == 0) {
            q.push(i);
        }
        // cout<<i<<": ";
        // for (auto &v : dag[i])cout<<v<<" ";
        // cout<<endl;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.emplace_back(u);
        for (auto &v : dag[u]) {
            if (!--in[v]) q.push(v);
        }
    }
    vector<ll>dp(n , 0);
    for (int i = topo.size() - 1;i >= 0;i--) {
        dp[topo[i]] = compressedWeights[topo[i]];
        for (auto &v : dag[topo[i]]) {
            dp[topo[i]] = max(dp[topo[i]] , dp[v] + compressedWeights[topo[i]]);
        }
    }
    cout<<*max_element(dp.begin() , dp.end())<<'\n';
}