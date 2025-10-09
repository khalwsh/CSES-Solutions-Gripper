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
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<int>adj[n];
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<int>dist(n,INT_MAX);
    dist[0]=0;
    vector<int>parent(n,0);
    for(int i=0;i<n;i++)parent[i]=i;
    queue<pair<int,int>>pq;
    pq.push({0,0});
    while(!pq.empty())
    {
        int node=pq.front().second;
        int cost=pq.front().first;
        pq.pop();
        if(cost!=dist[node])continue;
        for(auto &val:adj[node])
        {
            if(dist[val]>cost+1)
            {
                dist[val]=cost+1;
                parent[val]=node;
                pq.push({dist[val],val});
            }
        }
    }
    if(dist[n-1]==INT_MAX)
        cout<<"IMPOSSIBLE";
    else
    {
        vector<int>path;
        int temp=n-1;
        while(parent[temp]!=temp)
        {
            path.emplace_back(temp);
            temp=parent[temp];
        }
        path.emplace_back(0);
        reverse(path.begin(),path.end());
        cout<<path.size()<<line;
        for(auto &val:path)cout<<val+1<<" ";
    }
}