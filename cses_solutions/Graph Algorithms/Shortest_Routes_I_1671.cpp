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
vector<int>dikstra(int n,vector<pair<int,int>>adj[])
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    vector<int>dist(n,INT64_MAX);
    dist[0]=0;
    pq.push({0,0});
    while(!pq.empty())
    {
        int node=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        if(dist[node]!=cost)continue;
        for(auto &val:adj[node])
        {
            if(dist[val.first]>cost+val.second)
            {
                dist[val.first]=val.second+cost;
                pq.push({dist[val.first],val.first});
            }
        }
    }
    return dist;
}
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<pair<int,int>>adj[n];
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        a--,b--;
        adj[a].emplace_back(b,c);
    }
    vector<int>dist=dikstra(n,adj);
    for(auto&val:dist)cout<<val<<" ";
    cout<<line;
}
 