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
//#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
signed main() {
    khaled
    int n;
    cin>>n;
    vector<int>v(n);
    for(auto &val:v)
        cin>>val;
    stack<int>sk;
    vector<int>res(n);
    res[0]=0;
    sk.push(1);
    for(int i=1;i<n;i++)
    {
       while(!sk.empty()&&v[i]<=v[sk.top()-1])
           sk.pop();
       if(!sk.empty())
           res[i]=sk.top();
       sk.push(i+1);
    }
    for(auto &val:res)
        cout<<val<<" ";
}
 