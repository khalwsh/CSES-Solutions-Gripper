#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-9;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(long long a1,long long b1,long long a2,long long b2,long long a3,long long b3) {return (a3 - a1) * (b2 - b1) == (a2 - a1) * (b3 - b1);}
const int N=2e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17+1;
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
struct SegmentTree{
    int n;
    vector<int>tree;
    SegmentTree(int _n){
        n=_n;
        tree.resize(4*n);
    }
    void build(int node,int nl,int nr,vector<int>&v){
        if(nl==nr){
            tree[node]=v[nl];
            return ;
        }
        int mid=nl+(nr-nl)/2;
        build(2*node+1,nl,mid,v);
        build(2*node+2,mid+1,nr,v);
        tree[node]=max(tree[2*node+1],tree[node*2+2]);
    }
    void update(int node,int nl,int nr,int index,int newValue){
        if(nl==nr&&nl==index){
            tree[node]+=newValue;
            return;
        }
        if(nl==nr)return;
        int mid=nl+(nr-nl)/2;
        if(nl>index||nr<index)return;
        update(2*node+1,nl,mid,index,newValue);
        update(2*node+2,mid+1,nr,index,newValue);
        tree[node]=max(tree[2*node+1],tree[2*node+2]);
    }
    int query(int node,int nl,int nr,int l,int r){
        if(nl>=l&&nr<=r)return tree[node];
        if(nl>r||nr<l)return -inf;
        int mid=nl+(nr-nl)/2;
        return max(query(2*node+1,nl,mid,l,r),query(2*node+2,mid+1,nr,l,r));
    }
};
signed main() {
    khaled
    int n,q;
    cin>>n>>q;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    SegmentTree seg(n);
    seg.build(0,0,n-1,v);
    while(q--){
        int x;
        cin>>x;
        int pos=-1;
        int left=0,right=n-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(seg.query(0,0,n-1,left,mid)>=x){
                pos=mid;
                right=mid-1;
            }else
                left=mid+1;
        }
        cout<<pos+1<<" ";
        if(pos!=-1)seg.update(0,0,n-1,pos,-x);
    }
}