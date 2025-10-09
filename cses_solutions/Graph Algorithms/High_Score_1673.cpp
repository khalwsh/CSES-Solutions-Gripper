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
const int N = 5001;
vector<int>adj[N];
int main() {
    PRE();
    int n , m;cin>>n>>m;
    vector<array<ll , 3>>edges(m);
    for (auto &[u ,  v , w] : edges) {
        cin>>u>>v>>w;
        w = -w;
        u-- , v--;
    }
    vector<ll>dist(n , inf);
    dist[0] = 0;
    for (int i = 0;i < n - 1;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[u] < inf) dist[v] = min(dist[u] + w , dist[v]);
        }
    }
    auto ref = dist;
    vector<int>cyclic(n , false);
    for (int i = 0;i < n;i++) {
        for (auto &[u , v , w] : edges) {
            if (dist[u] < inf && dist[v] > dist[u] + w) dist[v] = -inf , cyclic[v] = true;
        }
    }
    if (cyclic[n - 1]) {
        cout<<-1;
    }else
        cout<<-dist[n - 1];
}