#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 1001;
int n , m;
int dp[N][N] , a[N] , b[N];
pair<int , int> parent[N][N];
 
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i <= n;i++) for (int j = 0;j <= m;j++)
        parent[i][j] = {-1 , -1};
    for (int i = 0;i < n;i++) cin >> a[i];
    for (int i = 0;i < m;i++) cin >> b[i];
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            if (a[i - 1] == b[j - 1]) {
                if (dp[i][j] < dp[i - 1][j - 1] + 1) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    parent[i][j] = {i - 1 , j - 1};
                }
            }else {
                if (dp[i][j] < dp[i][j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                    parent[i][j] = {i , j - 1};
                }
                if (dp[i][j] < dp[i - 1][j]) {
                    dp[i][j] = dp[i - 1][j];
                    parent[i][j] = {i - 1 , j};
                }
            }
        }
    }
    vector<int>seq;
    int mx = dp[n][m];
    pair<int , int>s = {n , m};
    while (seq.size() != mx) {
        auto [i , j] = parent[s.first][s.second];
        if (i == s.first - 1 && j == s.second - 1) seq.emplace_back(a[i]);
        s = {i , j};
    }
    reverse(seq.begin() , seq.end());
    cout<<mx<<'\n';
    for (auto &val : seq) cout << val << " ";
}