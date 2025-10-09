#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int main(){
    PRE();
    int n;cin >> n;
    map<int ,int>mp;
    ll res = 0;
    int left = 0;
    vector<int>v(n);
    for (int i = 0;i < n;i++) {
        int x;cin >> x;mp[x]++;
        v[i] = x;
        while (mp.size() != i - left + 1) {
            mp[v[left]]--;
            if (mp[v[left]] == 0) mp.erase(v[left]);
            left++;
        }
        res += i - left + 1;
    }
    cout << res << '\n';
}