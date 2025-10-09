#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 1 , k = 30;
int n , q;
vector<int>adj[N];
int up[k][N];
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        up[0][i] = x - 1;
    }
    for(int i = 1;i < k;i++) {
        for(int j = 0;j < n;j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    while(q--) {
        int node , kth;cin>>node>>kth;
        node--;
        for(int i = 0;i < k;i++) {
            if(kth & (1<<i)) {
                node = up[i][node];
            }
        }
        cout<<node + 1<<'\n';
    }
}