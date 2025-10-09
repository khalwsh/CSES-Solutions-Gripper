#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n;
ll dp[N];
array<ll , 3>v[N];
int nxt[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    vector<ll>f;
    for(int i = 0;i < n;i++) {
        cin>>v[i][0]>>v[i][1]>>v[i][2];
        nxt[i] = n + 1;
        f.emplace_back(v[i][0]);
    }
    sort(f.begin() , f.end());
    sort(v , v + n );
    for(int i = 0;i < n;i++) {
        nxt[i] = upper_bound(f.begin() , f.end() , v[i][1]) - f.begin();
    }
    for(int i = 0;i < n;i++) {
        dp[i + 1] = max(dp[i + 1] , dp[i]);
        dp[nxt[i]] = max(v[i][2] + dp[i] , dp[nxt[i]]);
    }
    cout<<dp[n];
}