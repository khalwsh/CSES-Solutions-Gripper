#include<bits/stdc++.h>
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
long long fast_power(long long base,long long power,long long m);
int counter=0;
void towerOfHanoi(int n, int from_rod, int to_rod,int aux_rod);
int main()
{
    khaled
    int n;
    cin>>n;
    cout<<(1<<n)-1;
    cout<<line;
    towerOfHanoi(n,1,3,2);
 
}
void towerOfHanoi(int n, int from_rod, int to_rod,int aux_rod)
{
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout<< from_rod<< " " << to_rod << line;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}
long long fast_power(long long base,long long power,long long m)
{
    if(power==1||power==0)
        return base*power+(!power);
    long long res=(fast_power(base,power/2,m)%m)%m;
    if(power&1)
        return(((((base%m)*(res%m))%m)*(res%m))%m)%m;
    else
        return ((res%m)*(res%m))%m;
}