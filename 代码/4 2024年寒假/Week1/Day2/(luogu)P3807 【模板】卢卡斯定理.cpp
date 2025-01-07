#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int qpow(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1) ans=(ans*x)%mod;
		y>>=1;
		x=(x*x)%mod;
	}
	return ans%mod;
}
int fac[N],inv[N];
void init(int mod){
	fac[0]=1;
	for(int i=1;i<=mod;i++)fac[i]=fac[i-1]*i%mod;
	inv[mod-1]=qpow(fac[mod-1],mod-2,mod);
	for(int i=mod-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m,int mod){
	if(m>n) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int lucas(int n,int m,int mod){
	if(m==0) return 1;
	return lucas(n/mod,m/mod,mod)*C(n%mod,m%mod,mod)%mod;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,mod;
		cin>>n>>m>>mod;
		init(mod);
		cout<<lucas(n+m,m,mod)<<"\n";
	}
}