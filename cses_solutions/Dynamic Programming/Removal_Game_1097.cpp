#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n , arr[5001];
const int N = 5001;
ll dp[N][N][2];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>arr[i];
    for(int i = 0;i < n;i++)for(int j = 0;j < n;j++) {
        dp[i][j][0] = 0;
        dp[i][j][1] = 1e15;
    }
    for(int i = 0;i < n;i++) {
        dp[i][i][0] = arr[i];
        dp[i][i][1] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j][0] = max(
                arr[i] + dp[i + 1][j][1],
                arr[j] + dp[i][j - 1][1]
            );
 
            dp[i][j][1] = min(
                dp[i + 1][j][0],
                dp[i][j - 1][0]
            );
        }
    }
    // cout<<dp[0][n - 1][0]<<"\n";
    cout<<dp[0][n - 1][0]<<"\n";
}