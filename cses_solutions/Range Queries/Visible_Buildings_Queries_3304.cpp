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
 
template<class T>
struct Fenwick{
    int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
        N = log2_floor(n) + 1;
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    T get(int pos) {
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
    int lower_bound(T t){
        T sum = 0;
        int pos = 0;
        for(int i = N; i >= 0; i--){
            int next_pos = pos + (1 << i);
            if(next_pos <= n && sum + tree[next_pos - 1] < t){
                sum += tree[next_pos - 1];
                pos = next_pos;
            }
        }
        return pos; // zero-based index
    }
};
 
int main() {
    PRE();
    int n , q;cin >> n >> q;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    vector<pair<int , int>>queries[n];
    for (int i = 0;i < q;i++) {
        int l , r;cin >> l >> r;
        l-- , r--;
        queries[l].emplace_back(r , i);
    }
    Fenwick<ll> fen;
    fen.init(n);
    vector<int>ans(q);
    set<pair<int ,int>>exist;
    for (int i = n - 1;i >= 0;i--) {
        auto it = exist.upper_bound({v[i] , 1e9});
        for (auto nxt = exist.begin(); nxt != it;nxt++) {
            auto [val , idx] = *nxt;
            fen.add(idx , -1);
        }
        fen.add(i , 1);
        exist.erase(exist.begin() , it);
        exist.insert({v[i] , i});
        for (auto &[r , idx] : queries[i]) {
            ans[idx] = fen.query(i , r);
        }
    }
    for (int i = 0;i < q;i++) cout << ans[i] << "\n";
}