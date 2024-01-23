#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=1e9+7;
int get_phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans-=ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans-=ans/n;
    return ans;
}
signed main(){
    int n,k;
    cin>>n>>k;
    while(k&&n>1){
        if(k&1)n=get_phi(n);
        k--;
    }
    cout<<n%mod;
}