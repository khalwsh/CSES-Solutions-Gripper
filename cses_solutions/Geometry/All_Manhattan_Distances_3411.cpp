#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
i128 solve(const vector<int> &v) {
    vector<int> a = v;
    sort(a.begin(), a.end());
    i128 cnt = 0, res = 0, sum = 0;
    int n = (int) a.size();
    for (int i = 0; i < n; ++i) {
        // use i128 casts to avoid 64-bit intermediate overflow
        res += (i128) a[i] * cnt - sum;
        sum += (i128) a[i];
        ++cnt;
    }
    return res;
}
 
void print_i128(i128 x) {
    if (x == 0) {
        cout << '0';
        return;
    }
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    string s;
    while (x > 0) {
        int d = int(x % 10);
        s.push_back(char('0' + d));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    cout << s;
}
 
int main() {
    PRE();
    int n;
    if (!(cin >> n)) return 0;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
 
    i128 ans = solve(x) + solve(y); // unordered pairs sum of Manhattan distances
    // If problem expects ordered pairs (count both directions), multiply by 2:
    // ans *= 2;
 
    print_i128(ans);
    cout << '\n';
    return 0;
}