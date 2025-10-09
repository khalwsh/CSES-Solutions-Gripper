#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int n;
string s;
int dp[1002][102];
const int mod = 1e9 + 7;
 
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    cin >> n >> s;
    vector<int> failure(s.size(), 0);
 
    for (int j = 1; j < s.size(); j++) {
        int i = failure[j - 1];
        while (i > 0 && s[i] != s[j])
            i = failure[i - 1];
        if (s[i] == s[j])
            i++;
        failure[j] = i;
    }
 
    int m = s.size();
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    // dp[i][j] : reprsent how many way you can create string of length i matching j-characters from the suffix but don't contain string pattern
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                int nxt = j;
                while (nxt > 0 && s[nxt] != c)
                    nxt = failure[nxt - 1];
                if (s[nxt] == c)
                    nxt++;
                dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][j]) % mod;
            }
        }
    }
 
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res = (res + dp[n][i]) % mod;
    }
 
    ll total = binpow(26, n, mod);
    ll answer = (total - res + mod) % mod;
 
    cout << answer << endl;
}