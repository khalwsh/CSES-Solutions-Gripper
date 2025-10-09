#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const int&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const int&mod){return (((x%mod)+(y%mod))+mod)%mod;}
int dx[]{1,-1,0,0};
int dy[]{0,0,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
class dsu{
private:
public:
    vector<int>parent;
    vector<int>siz;
    dsu()=default;
    dsu(int n)
    {
        //intializing the parent and rank
        parent.resize(n+1);
        siz.resize(n+1,1);
        for(int i=0;i<=n;i++)
            parent[i]=i;
    }
    int find_parent(int child)
    {
        //this function find the ultimate parent of certain child and make a update the parent
        if(parent[child]==child)
            return child;
        return parent[child]=find_parent(parent[child]);
    }
    void union_by_size(int a,int b)
    {
        int pa= find_parent(a);
        int pb= find_parent(b);
        if(pa==pb)return;
        if(siz[pa]>=siz[pb])
            siz[pa]+=siz[pb],parent[pb]=pa;
        else if(siz[pb]>siz[pa])
            siz[pb]+=siz[pa],parent[pa]=pb;
    }
    bool same_component(int a,int b)
    {
        return find_parent(a)==find_parent(b);
    }
};
long long nc2(long long res)
{
    return res*(res-1)/2;
}
bool comp(pair<int,pair<int,int>>&a,pair<int,pair<int,int>>&b)
{
    return a.second.second<b.second.second;
}
signed main() {
    khaled
    int n;
    cin>>n;
    int m,d;
    cin>>m>>d;
    vector<int>v(n);
    for(auto &val:v)
        cin>>val;
    vector<int>app(m);
    for(auto &val:app)cin>>val;
    sort(v.begin(),v.end());
    int res=0;
    sort(app.begin(),app.end());
    int pointer1=0;
    for(int i=0;i<n;i++)
    {
        while(pointer1<m&&app[pointer1]+d<v[i])pointer1++;
        if(pointer1<m&&app[pointer1]>v[i])
        {
            if(v[i]+d>=app[pointer1])res++,pointer1++;
        }
        else if(pointer1<m)
        {
            if(app[pointer1]+d>=v[i])res++,pointer1++;
        }
    }
    cout<<res<<line;
}