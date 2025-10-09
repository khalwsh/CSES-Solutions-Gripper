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
const ll inf = 1e18;
int main() {
    PRE();
    int n , m;cin>>n>>m;
    vector<array<ll , 3>>edges(m);
    for (auto &[u , v , w] : edges) {
        cin >> u >> v >> w;
        u-- , v--;
    }
    vector<ll>dist(n , inf) , prev(n , -1);
    int cyclic_node = -1;
    for (int i = 0;i < n;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (i == n - 1)
                    cyclic_node = (int)v;
                prev[v] = u;
            }
        }
    }
    if (cyclic_node == -1) {
        cout<<"NO";
    }else {
        for (int i = 0;i < n;i++) {
            cyclic_node = prev[cyclic_node];
        }
        cout<<"YES\n";
        vector<int>cycle;
        for (int i = cyclic_node;i != cyclic_node || cycle.size() == 0; i = prev[i]) {
            cycle.emplace_back(i);
        }
        cycle.emplace_back(cyclic_node);
        reverse(cycle.begin() , cycle.end());
        for (auto &v : cycle)
            cout<<v + 1<<" ";
    }
}