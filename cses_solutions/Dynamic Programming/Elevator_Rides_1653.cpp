#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n , m;cin>>n>>m;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    pair<int , ll>dp[1<<n];
    for(int i = 0;i < (1<<n);i++)dp[i] = make_pair(1e9 , 1e18);
    dp[0] = {1 , 0};
    for(int i = 1;i < (1<<n);i++) {
        for(int j = 0;j < n;j++) {
            if(i & (1<<j)){
                auto [x , y] = dp[i ^ (1<<j)];
                if(v[j] + y <= m) {
                    dp[i] = min(dp[i] , {x , y + v[j]});
                }else
                    dp[i] = min(dp[i]  , {x + 1 , v[j]});
            }
        }
    }
    cout<<dp[(1<<n) - 1].first;
}