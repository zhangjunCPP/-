#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e6+10,mod=998244353;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int fac[N],inv[N],poww[N];
int dp[N];

void init(){
    fac[0]=inv[0]=poww[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod,poww[i]=poww[i-1]*2%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    dp[0]=1,dp[1]=0;
    for(int i=2;i<N;i++)dp[i]=(dp[i-1]+dp[i-2]*2*(i-1)%mod)%mod*4*i%mod*(i-1)%mod;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void solve(){
    int n;
    cin>>n;
    for(int k=0;k<=n;k++)cout<<C(n,k)*C(n,k)%mod*fac[k]%mod*poww[k]%mod*dp[n-k]%mod<<"\n";
}
signed main(){
    init();
    int T;
    cin>>T;
    while(T--)solve();
}