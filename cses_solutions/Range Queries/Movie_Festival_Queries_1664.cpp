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
const int N = 1e6 + 10 , K = 20;
int up[N][K];
int main() {
    PRE();
    int n , q; cin >> n >> q;
    vector<pair<int , int>> v(n);
    for (int i = 0;i < n;i++) cin >> v[i].first >> v[i].second;
    sort(v.begin() , v.end());
 
    for (int i = 0;i < N;i++)
        for (int j = 0;j < K;j++)
            up[i][j] = N - 1;
 
    for (int i = n - 2;i >= 0;i--)
        v[i].second = min(v[i].second , v[i + 1].second);
 
    int k = 0;
    for (int i = 0;i < N;i++) {
        while (k < v.size() && v[k].first < i)k++;
        up[i][0] = (k == v.size() ? N - 1 : v[k].second);
        // if (i <= 10) cout << i << " " << up[i][0] << endl;
    }
 
    for (int i = 1;i < K;i++) {
        for (int j = 0;j < N;j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
    while (q--) {
        int l , r; cin >> l >> r;
        int ans = 0;
        for (int i = K - 1;i >= 0;i--) {
            // cout << l << " " << up[l][i] << endl;
            if (up[l][i] <= r) {
                l = up[l][i];
                ans += 1 << i;
            }
        }
        cout << ans << '\n';
    }
}