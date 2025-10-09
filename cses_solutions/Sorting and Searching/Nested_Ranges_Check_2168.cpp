#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool comp(pair<long long,long long>&a,pair<long long,long long>&b)
{
   if(a.first!=b.first)
       return a.first<b.first;
   else
       return a.second>b.second;
 
}
int main() {
    khaled
    int n;
    cin>>n;
    vector<pair<long long,long long>>vp(n);
    for(auto &val:vp)cin>>val.first>>val.second;
    vector<bool>some_one_have_me(n,false);
    map<pair<int,int>,int>mp;
    for(int i=0;i<n;i++)
        mp[vp[i]]=i;
    sort(vp.begin(),vp.end(),comp);
 
    long long max_right=vp[0].second;
    for(int i=1;i<n;i++)
    {
        if(vp[i].second<=max_right)
        {
            some_one_have_me[i]=true;
        }
        max_right=max(max_right,vp[i].second);
    }
    vector<bool>i_contain_range(n,false);
    long long min_right=INT_MAX;
    for(int i=n-1;i>=0;i--)
    {
        if(vp[i].second>=min_right)
        {
            i_contain_range[i]=true;
        }
        if(some_one_have_me[i])
            min_right=min(vp[i].second,min_right);
    }
    vector<bool>final_res(n),final_res2(n);
    for(int i=0;i<n;i++)
    {
        final_res[mp[vp[i]]]=i_contain_range[i];
        final_res2[mp[vp[i]]]=some_one_have_me[i];
    }
    for(int i=0;i<n;i++)
        cout<<final_res[i]<<" ";
    cout<<line;
    for(int i=0;i<n;i++)
    {
        cout<<final_res2[i]<<" ";
    }
}