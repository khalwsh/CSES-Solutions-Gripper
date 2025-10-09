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
const int k=20;
int BinaryLifting[k][N],depth[N],parent[N];
vector<int>adj[N];
void MarkDepth(int node=0,int par=-1,int dep=0){
    depth[node]=dep;
    for(auto &val:adj[node]){
        if(val!=par)MarkDepth(val,node,dep+1);
    }
}
void build(int n){
    for(int i=0;i<n;i++){
        BinaryLifting[0][i]=parent[i];
    }
    for(int i=1;i<k;i++){
        for(int j=0;j<n;j++){
            BinaryLifting[i][j]=BinaryLifting[i-1][BinaryLifting[i-1][j]];
        }
    }
}
int Walk(int node,int kth){
    if(depth[node]<kth)return -2;
    for(int i=0;i<k;i++){
        if(kth&(1<<i))node=BinaryLifting[i][node];
    }
    return node;
}
int LCA(int a,int b){
 
    if(depth[a]<depth[b])swap(a,b);
    a=Walk(a,depth[a]-depth[b]);
    if(a==b)return a;
    for(int i=k-1;i>=0;i--){
        if(BinaryLifting[i][a]!=BinaryLifting[i][b]){
            a=BinaryLifting[i][a];
            b=BinaryLifting[i][b];
        }
    }
    return parent[a];
}
signed main() {
    khaled
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int x;
        cin>>x;
        x--;
        parent[i]=x;
        adj[i].emplace_back(x);
        adj[x].emplace_back(i);
    }
    build(n);
    MarkDepth();
    while(q--){
        int node,kth;
        cin>>node>>kth;
        node--;
        cout<<LCA(node,kth-1)+1<<line;
    }
}