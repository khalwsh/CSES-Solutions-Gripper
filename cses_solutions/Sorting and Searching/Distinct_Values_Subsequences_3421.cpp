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
const int N = 2e5 + 10 , mod = 1e9 + 7;
ll inv[N] , FInv[N] , fact[N];
void Inverse() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
void FactorialInverse() {
    FInv[0] = FInv[1] = 1;
    for (int i = 2; i < N; i++)
        FInv[i] = (inv[i] * FInv[i - 1]) % mod;
}
void factorial() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
}
int Ncr(int n, int r) {
    if(r > n)return 0;
    ll ans = ((fact[n] * FInv[r])
               % mod * FInv[n - r])
              % mod;
    return ans;
}
void init() {
    Inverse();
    FactorialInverse();
    factorial();
}
int main(){
    PRE();
    init();
    int n;cin >> n;
    vector<int>v(n);
    map<int ,int>freq;
    for (auto &val : v) cin >> val , freq[val]++;
    int res = 1;
    for (auto &[v , f] : freq) {
        res = 1LL * res * (Ncr(f , 1) + 1) % mod;
    }
    res = (res - 1 + mod) % mod;
    cout << res << "\n";
}