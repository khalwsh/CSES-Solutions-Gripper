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
const int N = 502;
ll cost[N][N];
const ll INF = 1e18;
ll dp[N][N];
int main() {
    PRE();
    int n , m , q;cin>>n>>m>>q;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            cost[i][j] = INF;
 
        }
        cost[i][i] = 0;
    }
    for (int i = 0;i < m;i++) {
        ll u , v , w;cin>>u>>v>>w;
        w = min(w , cost[u - 1][v - 1]);
        cost[u - 1][v - 1] = w;
        swap(u , v);
        cost[u - 1][v - 1] = w;
    }
    for (int j = 0;j < n;j++) {
        for (int k = 0;k < n;k++) {
            dp[j][k] = INF;
        }
    }
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            dp[i][j] = cost[i][j];
        }
    }
    for (int k = 0;k < n;k++) {
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]);
            }
        }
    }
    while (q--) {
        int u , v;cin>>u>>v;
        u-- , v--;
        cout<<(dp[u][v] == INF ? -1 : dp[u][v])<<'\n';
    }
}