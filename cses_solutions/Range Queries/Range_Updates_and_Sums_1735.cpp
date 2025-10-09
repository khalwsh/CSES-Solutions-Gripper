#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
const int N = 2e5+9;
ll a[N];
struct info{
    int l,r; // boundary of block [l..r]
    ll sum , lazy_inc, lazy_set;
 
    void build(){
        sum = 0;
        for(int i = l; i <= r; ++i){
            if(lazy_set) a[i]  = lazy_set;
            if(lazy_inc) a[i] += lazy_inc;
            sum += a[i];
        }
        lazy_inc = 0;
        lazy_set = 0;
    }
    void inc(ll x){
        sum += (r-l+1) * x;
        lazy_inc += x;
    }
    void set(ll x){
        sum = (r-l+1) * x;
        lazy_set = x;
        lazy_inc = 0;
    }
    void inc(int lx , int rx , ll x){
        lx = max(l , lx); rx = min(rx , r);
        if(fill(lx,rx)){ inc(x); return; }
        build();
        for(int i = lx; i <= rx; ++i){
            sum -= a[i];
            a[i] += x;
            sum += a[i];
        }
    }
    void set(int lx , int rx , ll x){
        lx = max(l , lx); rx = min(rx , r);
        if(fill(lx,rx)) { set(x); return; }
        build();
        for(int i = lx; i <= rx; ++i){
            sum -= a[i];
            a[i] = x;
            sum += a[i];
        }
    }
    ll get_sum(int lx , int rx){
        lx = max(l , lx); rx = min(rx , r);
        if(fill(lx,rx)) return sum;
        build();
        ll res = 0;
        for(int i = lx; i <= rx; ++i){
            res += a[i];
        }
        return res;
    }
    bool fill(int lx , int rx){ return l == lx && r == rx; }
 
}Sqrt[N];
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n , q; cin >> n >> q;
    for(int i = 0; i < n; ++i) cin >> a[i];
 
    const int BLOCK_SIZE = sqrt(n)+1;
    int m = 0;
    for(int l = 0; l < n; l += BLOCK_SIZE){
        int r = min(n , l+BLOCK_SIZE) - 1;
        int ind = l / BLOCK_SIZE;
        Sqrt[ind] = info{l,r,0,0,0};
        Sqrt[ind].build();
        ++m;
    }
 
    auto valid = [&](int ind , int l , int r){
        return ind < m && Sqrt[ind].l <= r;
    };
 
    while(q--){
        int t; cin >> t;
        int l,r; cin >> l >> r;
        --l; --r;
        int ind = l / BLOCK_SIZE;
 
        if(t == 1){
            // increase [l..r] by x
            int x; cin >> x;
            while(valid(ind,l,r)) Sqrt[ind++].inc(l,r,x);
        }else if(t == 2){
            // set [l..r] by x
            int x; cin >> x;
            while(valid(ind,l,r)) Sqrt[ind++].set(l,r,x);
        }else{
            // sum [l..r]
            ll sum = 0;
            while(valid(ind,l,r)) sum += Sqrt[ind++].get_sum(l,r);
            cout << sum << '\n';
        }
    }
}