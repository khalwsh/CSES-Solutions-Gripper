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
const int N = 1e7 + 10;
bool is_pref[N];
int main(){
    PRE();
    for (int i = 0;i * i < N;i++) {
        is_pref[i * i] = true;
    }
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        for (int i = 0;i * i <= n;i++) {
            for (int j = i;j * j + i * i <= n;j++) {
                for (int k = j;k * k + j * j + i * i <= n;k++) {
                    if (is_pref[n - k * k - j * j - i * i]) {
                        cout << i << " " << j << " " << k << " " << sqrt(n - k * k - j * j - i * i) << '\n';
                        goto done;
                    }
                }
            }
        }
        done : ;
    }
}