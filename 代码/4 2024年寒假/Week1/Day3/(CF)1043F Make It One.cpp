#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int mod=998244353;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return ans%mod;
}
int fac[N],inv[N];
void init(){
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){
    if(m==0) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int sum[N];
int dp[N];
signed main(){
    init();
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sum[x]++;
    }
    for(int i=1;i<N;i++)for(int j=i*2;j<N;j+=i) sum[i]+=sum[j];
    for(int i=1;i<=7;i++){
        for(int j=N-1;j;j--){
            dp[j]=C(sum[j],i);
            for(int k=j*2;k<N;k+=j) dp[j]=(dp[j]-dp[k]+mod)%mod;
        }
        if(dp[1]){cout<<i;return 0;}
    }
    puts("-1");
    return 0;
}