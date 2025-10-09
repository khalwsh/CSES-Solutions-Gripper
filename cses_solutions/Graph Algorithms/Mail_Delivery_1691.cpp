#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 2e5 + 10;
int n,m;
set<int>adj[N];
int degree[N];
vector<int>tour;
void dfs(int node){
    while((int)adj[node].size()){
        int x = *adj[node].rbegin();
        adj[node].erase(x);
        if(adj[x].count(node)){
            adj[x].erase(node);
            dfs(x);
        }
    }
    tour.emplace_back(node);
}
bool check(){
    for(int i=0;i<n;i++){
        if(degree[i]&1){
            return false;
        }
    }
    return true;
}
bool get(){
    dfs(0);
    reverse(tour.begin(),tour.end());
    if(tour.size()!=m+1){
        return false;
    }
    return true;
}
int main() {
    PRE();
	cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int a , b;cin >> a >> b;
        a-- , b--;
        adj[a].insert(b);
        adj[b].insert(a);
        degree[a]++ , degree[b]++;
    }
    if (check() && get()) {
        for (auto &val : tour) cout << val + 1 <<" ";
    }else
        cout << "IMPOSSIBLE";
}