#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000;
ll capacity[N][N];
int n , m;
pair<ll, vector<int>> Get(int source, int sink) {
    vector<int> parent(n, -1);
    vector<ll> maxMinEdge(n, 0);
    maxMinEdge[source] = 2e9;
 
    priority_queue<pair<ll, int>> pq;
    pq.push({maxMinEdge[source], source});
 
    while (!pq.empty()) {
        ll currMaxMin = pq.top().first;
        int node = pq.top().second;
        pq.pop();
 
        if (currMaxMin < maxMinEdge[node]) continue;
 
        for (int next = 0; next < n; next++) {
            if (capacity[node][next] <= 0) continue;
            ll newMaxMin = min(maxMinEdge[node], capacity[node][next]);
 
            if (newMaxMin > maxMinEdge[next]) {
                maxMinEdge[next] = newMaxMin;
                parent[next] = node;
                pq.push({newMaxMin, next});
            }
        }
    }
 
    vector<int> path;
    if (maxMinEdge[sink] == 0) {
        return {0, path};
    }
 
    int current = sink;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return {maxMinEdge[sink], path};
}
ll MaxFlow(int source , int sink) {
    ll flow = 0;
    while(true) {
        // get path
        auto [NewFlow , dist] = Get(source , sink);
        if(!NewFlow)break;
        flow += NewFlow;
        // ugment it
        for(int i = 1;i < dist.size();i++) {
            capacity[dist[i - 1]][dist[i]] -= NewFlow;
            capacity[dist[i]][dist[i - 1]] += NewFlow;
        }
    }
    return flow;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i = 0;i < m;i++) {
        int u , v , c;cin>>u>>v>>c;
        u-- , v--;
        capacity[u][v] += c;
    }
    cout<<MaxFlow(0 , n - 1);
}