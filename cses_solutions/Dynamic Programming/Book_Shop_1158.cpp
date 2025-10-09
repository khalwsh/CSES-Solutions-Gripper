#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e5 + 1;
int h[N] , p[N];
int n;
vector<int> dp[2]; // max number of pages you can buy with i coins
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    int x;cin>>x;
    for(int i = 0;i < n;i++)cin>>h[i];
    for(int i = 0;i < n;i++)cin>>p[i];
    dp[0] = vector<int>(x + 1);
    dp[1] = vector<int>(x + 1);
    dp[0][0] = 0;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j <= x;j++)dp[1][j] = dp[0][j];
        for(int j = h[i];j <= x;j++) {
            dp[1][j] = max(dp[1][j] , dp[0][j - h[i]] + p[i]);
        }
        swap(dp[0] , dp[1]);
    }
    cout<<dp[0][x]<<'\n';
}