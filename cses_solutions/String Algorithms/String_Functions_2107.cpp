#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> zFunction(const string &s) {
    //it computes for every index i starts at i what is the largest string is matching a prefix
    int n = (int)s.size();
    vector<int> z(n);
    int left = 0, right = 0;
    for(int i = 1; i < n; i++) {
        if(i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while(i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}
vector<int>prefixFunction(const string &s) {
    vector<int>failure(s.size());
    for(int i = 1;i < s.size();i++) {
        int j = failure[i - 1];
        while(j > 0 && s[j] != s[i])j = failure[j - 1];
        if(s[j] == s[i])j++;
        failure[i] = j;
    }
    return failure;
}
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;cin>>s;
    for(auto &val:zFunction(s))cout<<val<<" ";
    cout<<'\n';
    for(auto &val:prefixFunction(s))cout<<val<<" ";
}