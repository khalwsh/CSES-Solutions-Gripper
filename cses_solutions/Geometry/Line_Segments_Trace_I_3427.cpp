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
const ll DEFAULT = LLONG_MIN;
const int N = 1e9+9;
 
struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {}
    ll operator()(ll x) const { return m * x + c; }
};
 
struct Node {
    Line line;
    Node *left = nullptr, *right = nullptr;
    Node(Line line = Line()) : line(line) {}
};
 
void insert(Line newLine, Node*& root, ll l = -N, ll r = N) {
    if (!root) {
        root = new Node(newLine);
        return;
    }
 
    ll m = (l + r) / 2;
    // (<) -> min f(x) , (>) -> max f(x)
    bool lef = newLine(l) > root->line(l);
    bool mid = newLine(m) > root->line(m);
 
    if (mid)
        swap(root->line, newLine);
 
    if (r - l == 1)
        return;
 
    if (lef != mid)
        insert(newLine, root->left, l, m);
    else
        insert(newLine, root->right, m, r);
}
 
ll query(ll x, Node* cur, ll l = -N, ll r = N) {
    if (!cur)
        return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return cur->line(x);
    if (x < m)
        return max(cur->line(x), query(x, cur->left, l, m));
    else
        return max(cur->line(x), query(x, cur->right, m, r));
}
int main() {
    PRE();
    int n , m;cin >> n >> m;
    Node*root = nullptr;
    for (int i = 0;i < n;i++) {
        int y1 , y2;cin >> y1 >> y2;
        //(0 , y1) ---> (m , y2)
        insert({((y2 - y1)) / (m) , y1}  , root);
    }
    for (int i = 0;i <= m;i++) cout << query(i , root) << ' ';
}