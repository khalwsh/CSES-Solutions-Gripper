#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
bitset<N>dp;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    dp[0] = true;
    int n;cin>>n;
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        dp |= dp<<x;
    }
    cout<<dp.count() - 1<<"\n";
    for(int i = 1;i <= N;i++) {
        if(dp[i])cout<<i<<" ";
    }
}