#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=998244353;
int fac[N],inv[N];
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void init() {
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=1;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main() {
	init();
	int n,m;
	cin>>n>>m;
	int ans=0;
	int opt=1;
	for(int i=0;i<=min(n,m);i++) {
		int val=C(n,i)*C(m,i)%mod*fac[i]%mod*qpow(n+1,m-i)%mod*qpow(m+1,n-i)%mod;
		ans=(ans+opt*val+mod)%mod;
		opt=-opt;
	}
	cout<<ans;
}