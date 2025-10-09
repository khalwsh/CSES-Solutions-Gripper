#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e6 + 10;
ll dp[N * 2];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n , x;cin>>n>>x;
    dp[0] = 1;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    for(int j = 0;j < n;j++) {
        for(int i = 0;i <= x;i++) {
            dp[i + v[j]] += dp[i];
            dp[i + v[j]] %= mod;
        }
    }
    cout<<dp[x]<<'\n';
}