#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e6+10;
int fac[N],inv[N],pw[N];
void init(){
    fac[0]=inv[0]=inv[1]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
    pw[0]=2;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*pw[i-1]%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
    int n,k;
    cin>>n>>k;
    init();
    int ans=0;
    for(int i=k;i<=n;i++){
        int tmp=C(i,k)*C(n,i)%mod*(pw[n-i]-1+mod)%mod;
        if((i-k)&1)ans=(ans-tmp+mod)%mod;
        else ans=(ans+tmp)%mod;
    }
    cout<<(ans+mod)%mod;
    return 0;
}