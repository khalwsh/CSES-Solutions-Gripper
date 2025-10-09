#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e6 + 10;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    memset(dp , '?' , sizeof dp);
    dp[0] = 0;
    for(int i = 1;i <= n;i++) {
        int temp = i;
        while(temp) {
            if(i - temp % 10 >= 0) dp[i] = min(dp[i] , 1 + dp[i - temp % 10]);
            temp /= 10;
        }
    }
    cout<<dp[n];
}