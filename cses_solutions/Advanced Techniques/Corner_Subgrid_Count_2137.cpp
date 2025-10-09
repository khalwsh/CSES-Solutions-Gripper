#include <bits/stdc++.h>
using namespace std;
#define static_assert(...);
#include <tr2/dynamic_bitset>
using custom_bitset = tr2::dynamic_bitset<long long>;
#pragma GCC target("popcnt")
 
// custom_bitset(10)
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
 
const int N = 3001;
custom_bitset arr[N];
 
int main() {
    PRE();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr[i] = custom_bitset(s);
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = (arr[i] & arr[j]).count();
            res += 1LL * x * (x - 1) / 2;
        }
    }
    cout << res << '\n';
}