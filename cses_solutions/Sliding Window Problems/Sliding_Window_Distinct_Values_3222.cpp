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
    int n , k;
    cin >> n >> k;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    map<int , int>freq;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            cout << freq.size() << ' ';
            freq[v[i - k]]--;
            if (freq[v[i - k]] == 0) freq.erase(v[i - k]);
        }
        freq[v[i]]++;
    }
    cout << freq.size() << ' ';
}