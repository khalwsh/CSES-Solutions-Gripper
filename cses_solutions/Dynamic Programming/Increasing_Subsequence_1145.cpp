#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int v[N] , comp[N] , n , dp[N];
template<class T>
struct Fenwick{
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]=max(tree[i - 1] , value);
    }
    T get(int pos) {
        if(pos < 0)return 0;
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum = max(sum , tree[i - 1]);
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>v[i] , comp[i] = v[i];
    sort(comp , comp + n);
    for(int i = 0;i < n;i++)v[i] = lower_bound(comp , comp + n , v[i]) - comp;
    Fenwick<int>fen;fen.init(n + 1);
    for(int i = 0;i < n;i++) {
        dp[i] = 1 + fen.get(v[i] - 1);
        fen.add(v[i] , -fen.query(v[i] , v[i]) + dp[i]);
        // cout<<dp[i]<<" ";
    }
    cout<<*max_element(dp , dp + n);
}