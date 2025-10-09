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
vector<int>adj[N];
int FirstNode=-1;
int dist[N];
int mx=0;
void dfs(int node,int par,int dis){
    if(mx<=dis){
        mx=dis;
        FirstNode=node;
    }
    for(auto &val:adj[node]){
        if(val==par)continue;
        dfs(val,node,dis+1);
    }
}
void mark(int node,int par,int dis){
    dist[node]=max(dist[node],dis);
    for(auto &val:adj[node]){
        if(val==par)continue;
        mark(val,node,dis+1);
    }
}
signed main() {
    khaled
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>q;
    dfs(0,-1,0);
    q.emplace(0,FirstNode);
    dfs(FirstNode,-1,0);
    q.emplace(0,FirstNode);
    while(!q.empty()) {
        mark(q.top().second, -1, 0);
        q.pop();
    }
    for(int i=0;i<n;i++){
        cout<<dist[i]<<" ";
    }
}