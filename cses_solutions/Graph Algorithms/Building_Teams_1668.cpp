#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))+mod)%mod;}
long long fast_power(long long base,long long power,const long long &mod=INT64_MAX){
    if(power==0)return 1ll;long long d= fast_power(base,power/2)%mod;d=mul(d,d,mod);if(power&1)return mul(d,base,mod);else return d;}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2);}//mod is prime
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
bool dfs_check(int node,int parent,vector<int>&color,vector<int>adj[],int co=0)
{
    color[node]=co;
    bool res=true;
    for(auto &val:adj[node])
    {
        if(color[val]==-1)
            res=res&&dfs_check(val,parent,color,adj,!co);
        else if(color[node]==color[val])
            res=false;
    }
    return res;
}
signed main() {
    khaled
    int n;
    cin>>n;
    int m;
    cin>>m;
    vector<int>adj[n];
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<int>vis(n,-1);
    bool is_pr=true;
    for(int i=0;i<n;i++)
    {
        if(vis[i]==-1)
            is_pr=is_pr&&dfs_check(i,-1,vis,adj);
    }
    if(is_pr)
    {
        for(auto &val:vis)
            cout<<val+1<<" ";
    }
    else
        cout<<"IMPOSSIBLE";
}