#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 4 , mod = 1e9 + 7;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    memset(dp , '?' , sizeof dp);
    dp[0] = 0;
    int n;cin>>n;
    int x;cin>>x;
    for(int i = 0;i < n;++i) {
        int y;cin>>y;
        for(int j = 0;j <= x;j++) {
            dp[j + y] = min(dp[j + y] , 1 + dp[j]);
        }
    }
    if(dp[x] >= 1e9)dp[x] = -1;
    cout<<dp[x];
}