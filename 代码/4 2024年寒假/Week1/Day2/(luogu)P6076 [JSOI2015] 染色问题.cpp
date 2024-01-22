#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e5+10;
int fac[N],inv[N];
void init(){
    fac[0]=inv[0]=inv[1]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int lucas(int n,int m){
    if(m==0)return 1;
    return lucas(n/mod,m/mod)%mod*C(n%mod,m%mod)%mod;
}
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=(ans*x)%mod;
        y>>=1;
        x=(x*x)%mod;
    }
    return ans%mod;
}
signed main(){
    init();
    int n,m,c;
    cin>>n>>m>>c;
    int ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=c;k++){
                int tmp=((i+j+k)&1)?-1:1;
                int g=C(n,i)*C(m,j)%mod*C(c,k)%mod*qpow(c-k+1,(n-i)*(m-j)%mod)%mod;
                ans=(ans+tmp*g+mod)%mod;
            }
        }
    }
    cout<<(ans+mod)%mod;
}