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
int a[N],m[N]={999911658,2,3,4679,35617};
const int mod=999911658;
int cnt=4,tot;
int crt(){
	int ans=0;
	for(int i=1;i<=cnt;i++){
		int M=mod/m[i];
		int mi=qpow(M,m[i]-2,m[i]);
		ans=(ans+a[i]%mod*M%mod*mi%mod)%mod;
	}
	return (ans+mod)%mod;
}
int n,g;
int tmp[N];
signed main(){
	cin>>n>>g;
	if(g%(mod+1)==0){
		puts("0");
		return 0;
	}
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			tmp[++tot]=i;
			if(i*i!=n) tmp[++tot]=n/i;
		}
	}
	for(int i=1;i<=cnt;i++){
		init(m[i]);
		for(int j=1;j<=tot;j++)a[i]=(a[i]+lucas(n,tmp[j],m[i]))%m[i];
	}
	cout<<qpow(g,crt(),mod+1);
}