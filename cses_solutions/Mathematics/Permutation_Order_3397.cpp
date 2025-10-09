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
// build factorials first
const int N = 21;
ll Fact[N];
vector<ll> nthPerm(ll len, ll nth) {
	vector<ll> identity(len), perm(len);
	for (int i = 0;i < len;i++) identity[i] = i;
 
	for (int i = len - 1; i >= 0; --i) {
		ll p = nth / Fact[i];
		perm[len - 1 - i] = identity[p];
		identity.erase(identity.begin() + p);
		nth %= Fact[i];
	}
	return perm;
}
ll PermToIndex(vector<int> perm) {
	ll idx = 0;
	int n = perm.size();
	for (int i = 0; i < n; ++i) {
		// Remove first, and Renumber the remaining elements to remove gaps
		idx += Fact[n-i-1] * perm[i];
		for(int j = i+1; j < n; j++)
			perm[j] -= perm[j] > perm[i];
	}
	return idx;
}
int main() {
    PRE();
	Fact[0] = 1;
	for (int i = 1;i < N;i++) Fact[i] = 1LL * i * Fact[i - 1];
	int t;cin >> t;
	while (t--) {
		int ty;cin >> ty;
		if (ty == 1) {
			ll n , k; cin >> n >> k;
			for (auto &val : nthPerm(n , k - 1)) cout << val + 1 << " ";
			cout << '\n';
		}else {
			int n;cin >> n;
			vector<int>perm(n);
			for (int i = 0;i < n;i++) cin >> perm[i] , perm[i]--;
			cout << PermToIndex(perm) + 1 << '\n';
		}
	}
}