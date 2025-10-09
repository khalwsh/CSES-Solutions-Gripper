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
 
int main() {
    PRE();
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        int a , b; cin >> a >> b;
        if (a + b > n || (a == 0 && b != 0) || (b == 0 && a != 0)) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 1;i <= n;i++) cout << i << " ";
            cout << '\n';
            for (int i = 1;i <= b;i++) cout << a + i << " ";
            for (int i = 1;i <= a;i++) cout << i << " ";
            for (int i = a + b + 1;i <= n;i++) cout << i << " ";
            cout << '\n';
        }
    }
}