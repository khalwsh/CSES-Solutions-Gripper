#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 1;
int v[N] , n;
struct SegmentTree {
    vector<int>tree;
    SegmentTree(int _n) {
        tree.resize(4 * _n);
    }
    void build(int node , int nl , int nr) {
        if(nl == nr) {
            tree[node] = 1;
            return;
        }
        int mid = nl + (nr - nl) /2 ;
        build(2 * node + 1 , nl , mid);
        build(2 * node + 2, mid + 1 , nr);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    void upd(int node , int nl , int nr , int idx) {
        if(nl == nr && nl == idx) {
            tree[node] = 0;
            return;
        }
        if(nl > idx || nr < idx)return;
        int mid = nl + (nr - nl) / 2;
        upd(2 * node + 1 , nl , mid , idx);
        upd(2 * node + 2 , mid + 1 , nr , idx);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    int query(int node , int nl , int nr , int k) {
        if(nl == nr)return nl;
        int mid = nl + (nr - nl) /2 ;
        if(tree[2 * node + 1] >= k)return query(2 * node + 1 , nl , mid , k);
        else {
            k -= tree[2 * node + 1];
            return query(2 * node + 2 , mid + 1 , nr , k);
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i = 0;i < n;i++) {
        cin>>v[i];
    }
    SegmentTree seg(n);
    seg.build(0 , 0 , n - 1);
    for(int i = 0;i < n;i++) {
        int pos;cin>>pos;
        auto kth = seg.query(0 , 0 , n - 1 , pos);
        cout<<v[kth]<<" ";
        seg.upd(0 , 0 ,n - 1 , kth);
    }
}