#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
struct RollBackDsu {
    vector<int> parent, size;
    vector<pair<int , int>> history;
    int cnt;
 
    RollBackDsu(int n) : cnt(n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
 
    int find(int a) {
        return (parent[a] == a ? a : find(parent[a]));
    }
 
    bool Merge(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) {
            history.emplace_back(-1 , -1);
            return false;
        }
        if(size[a] > size[b])
            swap(a, b);
        history.emplace_back(a , b);
        parent[a] = b;
        size[b] += size[a];
        cnt--;
        return true;
    }
 
    void rollback(int steps) {
        while(steps--) {
            auto [a , b] = history.back();
            history.pop_back();
            if (a == -1)continue;
            parent[a] = a;
            size[b] -= size[a];
            ++cnt;
        }
    }
};
int n , m , k;
struct event {
    int u , v;
};
const int N = 3e5 + 10;
vector<event>tree[N * 4];
void update(int node , int nl , int nr , int l , int r , const event &ev) {
    if (nl >= l && nr <= r) {
        tree[node].emplace_back(ev);
        return;
    }
    if (nl > r || nr < l)return;
    int mid = nl + (nr - nl) / 2;
    update(2 * node + 1 , nl , mid , l , r , ev);
    update(2 * node + 2 , mid + 1 , nr , l , r , ev);
}
int res[N];
RollBackDsu dsu(N);
void dfs(int node , int nl , int nr) {
    for (auto  &[u , v] : tree[node]) {
        dsu.Merge(u , v);
    }
    if (nl == nr) {
        res[nl] = dsu.cnt;
    }else {
        int mid = nl + (nr - nl) / 2;
        dfs(2 * node + 1 , nl , mid);
        dfs(2 * node + 2 , mid + 1 , nr);
    }
    dsu.rollback(tree[node].size());
}
int main() {
    PRE();
    cin>>n>>m>>k;
    map<pair<int , int> , int>lst;
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        if (u > v)swap(u , v);
        lst[{u , v}] = 0;
    }
    for (int i = 1;i <= k;i++) {
        int type;cin>>type;
        int u , v;cin>>u>>v;u-- , v--;
        if (u > v)swap(u , v);
        if (type == 1) {
            lst[{u , v}] = i;
        }else {
            update(0 , 0 , N - 1 , lst[{u , v}] , i - 1, {u , v});
            lst.erase({u , v});
        }
    }
    for (auto &[a , b] : lst) {
        update(0 , 0 , N - 1 , b , k , {a.first , a.second});
    }
    dfs(0  , 0 , N - 1);
    for (int i = 0;i <= k;i++) {
        cout<<res[i] - N + n <<" ";
    }
}