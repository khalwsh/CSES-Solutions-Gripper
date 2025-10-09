#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500 * 500 , mod = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    ll sum = n * (n + 1) / 2;
    if(sum & 1 ) {
        cout<<0<<'\n';
        exit(0);
    }
    vector<int>dp(sum + 1);
    dp[0] = 1;
    for(int i = 1;i <= n;i++) {
        int x;x = i;
        vector<int>ndp(sum + 1);
        for(int j = 0;j <= sum;j++)ndp[j] = dp[j];
        for(int j = 0;j + x <= sum;j++) {
            ndp[j + x] += dp[j];
            if(ndp[j + x] >= mod)ndp[j + x] -= mod;
        }
        swap(dp , ndp);
    }
    cout<<1LL * dp[sum / 2] * 500000004 % mod;
}