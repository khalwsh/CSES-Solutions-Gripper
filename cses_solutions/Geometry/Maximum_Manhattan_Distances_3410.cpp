#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
int main() {
    PRE();
    ll best[4];
    for (int i = 0; i < 4; i++) best[i] = -1e18;
    int n;
    cin >> n;
    vector<pair<ll, ll> > vp(n);
    for (auto &[x , y]: vp) cin >> x >> y;
    for (auto &[x , y]: vp) {
        best[0] = max(best[0], x + y);
        best[1] = max(best[1], x - y);
        best[2] = max(best[2], -x - y);
        best[3] = max(best[3], -x + y);
        cout << max(best[0] + best[2], best[1] + best[3]) << '\n';
    }
}