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
const int N = 501;
char v[N][N];
int n , m;
 
bool solve(int i , int j) {
    if (i == n) {
        return true;
    }
    for (auto &val : "ABCD") {
        if (val == v[i][j] || (i >= 1 && val == v[i - 1][j]) ||(j >= 1 && val == v[i][j - 1])) {
            continue;
        }
        char old = v[i][j];
        v[i][j] = val;
        if (solve(i + (j + 1 == m) , (j + 1) % m)) {
            return true;
        }
        v[i][j] = old;
    }
    return false;
}
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i < n;i++)
        for (int j = 0;j < m;j++)
            cin >> v[i][j];
    if (solve(0 , 0)) {
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++)
                cout << v[i][j];
            cout << '\n';
        }
    }else {
        cout << "IMPOSSIBLE";
    }
}