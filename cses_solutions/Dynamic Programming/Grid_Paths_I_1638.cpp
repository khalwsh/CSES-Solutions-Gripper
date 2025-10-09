#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e3 + 1;
char grid[N][N];
int dp[N][N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++)
            cin>>grid[i][j];
    }
    dp[0][0] = 1;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            if(!i && !j || grid[i][j] == '*')continue;
            if(i)dp[i][j] += dp[i - 1][j];
            if(dp[i][j] >= mod)dp[i][j] -= mod;
            if(j)dp[i][j] += dp[i][j - 1];
            if(dp[i][j] >= mod)dp[i][j] -= mod;
        }
    }
    if(grid[0][0] == '*')dp[n - 1][n - 1] = 0;
    cout<<dp[n - 1][n - 1];
}