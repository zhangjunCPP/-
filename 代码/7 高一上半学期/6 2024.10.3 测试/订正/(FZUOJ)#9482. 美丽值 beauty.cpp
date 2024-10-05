#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int pw1[N],pw2[N];
void solve(){
	int n,v;
	cin>>n>>v;
	int ans=0;
	for(int i=1;i<=v;i++){
		pw1[0]=1,pw2[0]=1;
		for(int j=1;j<=n;j++)pw1[j]=pw1[j-1]*i%mod,pw2[j]=pw2[j-1]*(v-i)%mod;
		for(int j=1;j<n;j++){
			int c0=j,c1=n-j;
			ans=(ans+C(n,c0)*pw1[c0]%mod*pw2[c1]%mod*min(c0,c1)%mod)%mod;
		}
	}
	cout<<ans*2%mod<<"\n";
}
signed main(){
	init();
	int T;
	cin>>T;
	while(T--)solve();
}