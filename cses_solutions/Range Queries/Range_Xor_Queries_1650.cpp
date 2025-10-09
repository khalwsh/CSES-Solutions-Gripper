#include<bits/stdc++.h>
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
int main() {
    khaled
    long long n,q;
    cin>>n>>q;
    vector<long long>v(n);
    vector<long long>v_xor(n);
    for(auto&val:v)
        cin>>val;
    v_xor[0]=v[0];
    for(int i=1;i<n;i++)
    {
        v_xor[i]=v_xor[i-1]^v[i];
    }
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        b--;
        a--;
        if(a==0)
            cout<<v_xor[b];
        else
            cout<<(v_xor[b]^v_xor[a-1]);
        cout<<line;
 
    }
}