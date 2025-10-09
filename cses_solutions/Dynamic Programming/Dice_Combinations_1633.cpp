#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 4 , mod = 1e9 + 7;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    dp[0] = 1;
    for(int i = 1;i < N;i++) {
        for(int j = 1;j <= 6;j++) {
            if(i - j >= 0){
                dp[i] += dp[i - j];
                if(dp[i] >= mod)dp[i] -= mod;
            }
        }
    }
    int n;cin>>n;
    cout<<dp[n];
}