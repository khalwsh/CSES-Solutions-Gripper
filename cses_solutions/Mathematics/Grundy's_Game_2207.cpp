#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int dp[2001];
 
int grundy(int x) {
    if (x == 0) return 0;
    int &ret = dp[x];
    if (~ret) return ret;
    vector<int> v;
    for (int a = 1; a <= x / 2; ++a) {
        int b = x - a;
        if (a == b) continue;
        int ga = grundy(a);
        int gb = grundy(b);
        v.emplace_back(ga ^ gb);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int mex = 0;
    while (mex < v.size() && v[mex] == mex) ++mex;
    return ret = mex;
}
 
int main() {
    PRE();
    memset(dp, -1, sizeof dp);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= 2000 || grundy(n)) cout << "first\n";
        else cout << "second\n";
    }
}