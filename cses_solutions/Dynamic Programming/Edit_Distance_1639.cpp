#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5001;
int dp[N][N];
string s , t;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    memset(dp , '?' , sizeof dp);
    cin>>s>>t;
    if(s.size() > t.size())swap(s , t);
    int n = s.size() , m = t.size();
    for(int i=0;i<=m;i++){
        dp[0][i] = i;
    }
    for(int i=0;i<=n;i++){
        dp[i][0] = i;
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            if(s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            dp[i][j] = min(dp[i][j] , 1 + dp[i - 1][j]);
            dp[i][j] = min(dp[i][j] , 1 + dp[i][j - 1]);
            dp[i][j] = min(dp[i][j] , 1 + dp[i - 1][j - 1]);
        }
    }
    cout<<dp[n][m];
}