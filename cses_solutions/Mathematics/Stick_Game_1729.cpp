#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , k;
    cin>>n>>k;
    vector<bool>w(n + 1);
    w[0] = false;
    vector<int>moves;
    for(int i = 0;i < k;i++) {
        int x;cin>>x;
        moves.emplace_back(x);
    }
    for(int i = 1;i <= n;i++) {
        bool ret = w[i];
        for(auto &val:moves) {
            if(i - val >= 0)ret = ret || !w[i - val];
            if(ret)break;
        }
        cout<<(ret ? "W" : "L");
        w[i] = ret;
    }
}