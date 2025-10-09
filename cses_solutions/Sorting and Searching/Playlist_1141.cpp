#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
const int N = 3e5 + 10;
int v[N];
int n;
int main() {
    PRE();
    cin>>n;
    for(int i = 0;i < n;i++) {
        cin>>v[i];
    }
    int l = 0 , r = 0 , mx = 1;
    map<int , int>mp;
    while(r < n) {
        mp[v[r]]++;
        while(mp[v[r]] > 1) {
            mp[v[l]]--;
            ++l;
        }
        mx = max(mx , r - l + 1);
        r++;
    }
    cout<<mx<<'\n';
}