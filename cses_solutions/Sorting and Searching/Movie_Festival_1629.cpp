#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 3;
int n;
pair<int , int>tasks[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>tasks[i].first>>tasks[i].second;
    sort(tasks , tasks + n , [&](pair<int , int>&a , pair<int , int>&b)->bool {
       return a.second < b.second;
    });
    int res = 0;
    int t = -1;
    for(int i = 0;i < n;i++) {
        if(tasks[i].first >= t)t = tasks[i].second , res++;
    }
    cout<<res<<'\n';
}