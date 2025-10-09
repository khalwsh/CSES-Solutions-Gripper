#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
int n , q;
const int sz = 1e9;
struct dynamicSeg {
    int sum = 0;
    dynamicSeg *left = nullptr, *right = nullptr;
    void add(int nl, int nr, int i, int delta) {
        if (nl == nr) {
            sum += delta;
            return;
        }
        int mid = (nl + nr) / 2;
        if (i <= mid) {
            if (!left) left = new dynamicSeg();
            left->add(nl, mid, i, delta);
        } else {
            if (!right) right = new dynamicSeg();
            right->add(mid + 1, nr, i, delta);
        }
        sum = (left ? left->sum : 0) + (right ? right->sum : 0);
    }
 
    int query(int nl , int nr , int l , int r) {
        if (nl >= l && nr <= r)return sum;
        if (nl > r || nr < l)return 0;
        int mid = nl + (nr - nl) / 2;
        auto res1 = left == nullptr ? 0 : left->query(nl , mid , l , r);
        auto res2 = right == nullptr ? 0 : right -> query(mid + 1 , nr , l , r);
        return  res1 + res2;
    }
};
int main() {
    PRE();
    dynamicSeg dseg;
    cin>>n>>q;vector<int>v(n);
    for (int i = 0;i < n;i++) {
        int x;cin>>x;v[i] = x;
        dseg.add(0 , sz - 1 , x , 1);
    }
    while (q--) {
        char ch;cin>>ch;
        if (ch == '!') {
            int k;cin>>k;int x;cin>>x;
            dseg.add(0 , sz - 1 , x , 1);
            dseg.add(0 , sz - 1 , v[k - 1] , -1);
            v[k - 1] = x;
        }else {
            int a , b;cin>>a>>b;
            cout<<dseg.query(0 , sz - 1 , a , b)<<'\n';
        }
    }
}