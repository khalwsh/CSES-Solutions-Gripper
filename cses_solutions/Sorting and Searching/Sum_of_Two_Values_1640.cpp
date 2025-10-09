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
vector<pair<int , int>>v;
int main() {
    PRE();
    int n , x;cin>>n>>x;
    for(int i = 0;i < n;++i) {
        int y;cin>>y;
        v.emplace_back(y , i);
    }
    sort(v.begin() , v.end());
    int p1 = 0 , p2 = v.size() - 1;
    while(p1 < p2) {
        if(v[p1].first + v[p2].first == x) {
            int l = v[p1].second , r = v[p2].second;
            if(l > r)swap(l , r);
            cout<<l + 1<<" "<<r + 1<<'\n';
            exit(0);
        }
        if(v[p1].first + v[p2].first > x) {
            p2--;
        }else
            p1++;
    }
    cout<<"IMPOSSIBLE\n";
}