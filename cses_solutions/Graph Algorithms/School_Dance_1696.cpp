#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
const int INF = 1e9; // Infinity value for unmatched nodes
 
// BFS Phase to build layers
bool bfs(int n, int m, vector<vector<int>>& adj, vector<int>& pairU, vector<int>& pairV, vector<int>& dist) {
    queue<int> q;
 
    // Initialize distances
    for (int u = 1; u <= n; ++u) {
        if (pairU[u] == 0) { // If the boy is unmatched
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF; // Sentinel for unmatched nodes
 
    // Perform BFS
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] < dist[0]) { // Check all neighbors
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
 
    return dist[0] != INF; // Returns true if there's an augmenting path
}
 
// DFS Phase to find augmenting paths
bool dfs(int u, vector<vector<int>>& adj, vector<int>& pairU, vector<int>& pairV, vector<int>& dist) {
    if (u != 0) { // Sentinel check
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v], adj, pairU, pairV, dist)) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}
 
// Hopcroft-Karp Algorithm
vector<pair<int , int>> hopcroftKarp(int n, int m, vector<vector<int>>& adj) {
    // graph should be 1 based
    vector<int> pairU(n + 1, 0); // Pairings for boys
    vector<int> pairV(m + 1, 0); // Pairings for girls
    vector<int> dist(n + 1);     // Distance array for BFS
 
    int matching = 0;
 
    // Repeat until no augmenting path exists
    while (bfs(n, m, adj, pairU, pairV, dist)) {
        for (int u = 1; u <= n; ++u) {
            if (pairU[u] == 0 && dfs(u, adj, pairU, pairV, dist)) {
                ++matching;
            }
        }
    }
 
    // Output the matches
    vector<pair<int , int>>matches;
    for (int v = 1; v <= m; ++v) {
        if (pairV[v] != 0) {
            matches.emplace_back(pairV[v] , v);
        }
    }
 
    return matches;
}
 
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
 
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
 
    // Call the Hopcroft-Karp algorithm
    auto res = hopcroftKarp(n, m, adj);
    cout<<res.size()<<"\n";
    for(auto &val:res)cout<<val.first<<" "<<val.second<<'\n';
    return 0;
}