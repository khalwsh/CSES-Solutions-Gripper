#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
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
const int N = 4e5 + 1;
int lst[N];
int main() {
    PRE();
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    memset(lst , -1 , sizeof lst);
    for (int i = 0; i < n; i++) cin >> v[i];
    set<int>all;
    for (int i = 0;i < N ;i++) all.insert(i);
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            cout << *all.begin() << " ";
            if (v[i - k] < N && lst[v[i - k]] == i - k ) all.insert(v[i - k]);
        }
        if (v[i] < N) {
            lst[v[i]] = i;
            if (all.count(v[i]))
             all.erase(v[i]);
        }
    }
    cout << *all.begin() << " ";
}