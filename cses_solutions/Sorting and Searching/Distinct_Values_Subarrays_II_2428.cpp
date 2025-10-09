#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int  n , k;
const int N = 2e5 + 5;
int x[N];
int main(){
    cin>>n>>k;
    for(int i = 0;i < n;i++)cin>>x[i];
    map<int , int>mp;
    int left = 0;
    ll res = 0;
    for(int i = 0;i < n;i++) {
        mp[x[i]]++;
        while(mp.size() > k) {
            mp[x[left]]--;
            if(mp[x[left]] == 0)mp.erase(x[left]);
            left++;
        }
        res += i - left + 1;
    }
    cout<<res<<endl;
}