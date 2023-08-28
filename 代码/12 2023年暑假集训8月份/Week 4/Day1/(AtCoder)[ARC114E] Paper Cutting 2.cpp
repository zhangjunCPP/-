#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
signed main(){
    int h,w,h1,w1,h2,w2;
    cin>>h>>w>>h1>>w1>>h2>>w2;
    int u=min(h1,h2)-1;
    int d=h-max(h1,h2);
    int l=min(w1,w2)-1;
    int r=w-max(w1,w2);
    int s=h+w-2;
    int ans=1;
    for(int i=1;i<=u;i++) ans=(ans+qpow(s-(d+l+r+i-1),mod-2))%mod;
    for(int i=1;i<=d;i++) ans=(ans+qpow(s-(u+l+r+i-1),mod-2))%mod;
    for(int i=1;i<=l;i++) ans=(ans+qpow(s-(d+u+r+i-1),mod-2))%mod;
    for(int i=1;i<=r;i++) ans=(ans+qpow(s-(d+l+u+i-1),mod-2))%mod;
    cout<<ans%mod;
}