#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool check_line(int a1,int b1,int a2,int b2,int a3,int b3){return (a3-a1)*(b2-b1)==(a2-a1)*(b3-b1);}
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &mod=INT64_MAX){if(power==0)return 1ll;long long d= fast_power(base,power/2)%mod;d=mul(d,d,mod);if(power&1)return mul(d,base,mod);else return d;}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2);}//mod is prime
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
vector<int> dikstra(int n,vector<pair<int,int>>adj[],map<pair<int,int>,int>&edges,int start,int target)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,start});
    vector<int>dist(n,1e17);
    dist[start]=0;
    vector<int>parent(n,0);
    while(!pq.empty())
    {
        int node=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        if(cost!=dist[node])continue;
        for(auto &val:adj[node])
        {
            if(dist[val.first]>dist[node]+val.second)
            {
                dist[val.first]=dist[node]+val.second;
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
    vector<pair<int,int>>adj[n],rev_adj[n];
    map<pair<int,int>,int>edges;
    for(int i=0;i<m;i++)
    {
        int a,b,cost;
        cin>>a>>b>>cost;a--,b--;
        adj[a].emplace_back(b,cost);
        rev_adj[b].emplace_back(a,cost);
        if(edges.count(make_pair(a,b))==0)edges[make_pair(a,b)]=cost;
        else edges[make_pair(a,b)]=min(edges[make_pair(a,b)],cost);
    }
    vector<int>dist_source= dikstra(n,adj,edges,0,n-1);
    vector<int>dist_target=dikstra(n,rev_adj,edges,n-1,0);
    long long ans=dist_source[n-1];
    for(int i=0;i<n;i++)
    {
        for(auto &val:adj[i])
        {
            ans=min(ans,dist_source[i]+dist_target[val.first]+val.second/2);
        }
    }
    cout<<ans<<line;
}
 