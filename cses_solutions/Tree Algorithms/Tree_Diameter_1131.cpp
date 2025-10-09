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
const int N = 2e5 + 10;
vector<int>adj[N];
int dp[N];
// dp[u]: maximum length of path in the tree pass throw u
int n;
int res = 0;
void dfs(int u , int p) {
    dp[u] = 1;
    for(auto &v:adj[u]) {
        if(v == p)continue;
        dfs(v , u);
    }
    vector<int>values;
    for(auto &val:adj[u]) {
        if(p != val){
            dp[u] = max(dp[u] , dp[val] + 1);
            if(values.size() >= 2) {
                if(dp[val] > values[0]) {
                    values[0] = dp[val];
                    sort(values.begin() , values.end());
                }
            }else {
                values.emplace_back(dp[val]);
                sort(values.begin() , values.end());
            }
        }
    }
    if(values.size() >= 2) {
        res = max(res , values[0] + 1 + values[1]);
    }
}
int main() {
    PRE();
    cin>>n;
    for(int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , -1);
    cout << max(*max_element(dp, dp + N), res) - 1;
}