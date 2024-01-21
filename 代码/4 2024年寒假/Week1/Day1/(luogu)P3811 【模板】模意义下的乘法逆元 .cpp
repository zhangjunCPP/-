#include <bits/stdc++.h>
#define int long long
const int N=3e6+10;
using namespace std;
int inv[N];
signed main(){
    int n,mod;
    cin>>n>>mod;
    inv[1]=1;
    for(int i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=n;i++)cout<<inv[i]<<"\n";
}