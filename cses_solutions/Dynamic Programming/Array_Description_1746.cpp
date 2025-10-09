#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10 , mod = 1e9 + 7;
int n , m;
int v[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n>>m;
    vector<int>dp(m + 1);
    for(int i = 0;i < n;i++)cin>>v[i];
    if(v[0] == 0)for(int i = 1;i <= m;i++)dp[i] = 1;
    else dp[v[0]] = 1;
    for(int i = 1;i < n;i++) {
        vector<int>ndp(m + 1);
        if(!v[i]) {
            // wild card
            for(int j = 1;j <= m;j++) {
                ndp[j] += dp[j];
                if(ndp[j] >= mod)ndp[j] -= mod;
                if(j - 1 > 0)ndp[j] += dp[j - 1];
                if(ndp[j] >= mod)ndp[j] -= mod;
                if(j + 1 <= m)ndp[j] += dp[j + 1];
                if(ndp[j] >= mod)ndp[j] -= mod;
            }
        }else {
            int j = v[i];
            ndp[j] += dp[j];
            if(ndp[j] >= mod)ndp[j] -= mod;
            if(j - 1 > 0)ndp[j] += dp[j - 1];
            if(ndp[j] >= mod)ndp[j] -= mod;
            if(j + 1 <= m)ndp[j] += dp[j + 1];
            if(ndp[j] >= mod)ndp[j] -= mod;
        }
        swap(ndp , dp);
    }
    ll sum = 0;
    for(auto &val:dp)sum += val , sum %= mod;
    cout<<sum;
}