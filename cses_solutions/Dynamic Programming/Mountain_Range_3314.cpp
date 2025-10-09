#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
vector<int> getNxtMax(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
vector<int> getPrevMax(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = arr.size() - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
 
struct SegmentTree {
    vector<int> tree;
    SegmentTree(int n) {
        tree.assign(4 * n, 0);
    }
    void upd(int node, int nl, int nr, int i, int nw) {
        if (nl > i || nr < i) return;
        if (nl == nr) {
            tree[node] = max(tree[node], nw);
            return;
        }
        int mid = (nl + nr) / 2;
        upd(2 * node + 1, nl, mid, i, nw);
        upd(2 * node + 2, mid + 1, nr, i, nw);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }
    int query(int node, int nl, int nr, int l, int r) {
        if (nl > r || nr < l) return 0;
        if (nl >= l && nr <= r) return tree[node];
        int mid = (nl + nr) / 2;
        return max(query(2 * node + 1, nl, mid, l, r),
                   query(2 * node + 2, mid + 1, nr, l, r));
    }
};
 
 
const int N = 2e5 + 10;
int n;
int main(){
    PRE();
    int n;
    if (!(cin >> n)) return 0;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
 
    auto nxt = getNxtMax(v);
    auto prv = getPrevMax(v);
 
    vector<pair<int,int>> temp(n);
    for (int i = 0; i < n; ++i) temp[i] = {v[i], i};
    sort(temp.begin(), temp.end(), [](const auto &a, const auto &b){
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    vector<int> dp(n, 0);
    SegmentTree seg(n);
    for (int i = 0; i < n; ++i) {
        int idx = temp[i].second;
        int l = prv[idx] + 1;
        int r = (nxt[idx] == -1 ? n-1 : nxt[idx] - 1);
        dp[i] = 1 + seg.query(0, 0, n-1, l, r);
        seg.upd(0, 0, n-1, idx, dp[i]);
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}