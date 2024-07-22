#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2)%mod;
	for(int i=N-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m) {
	if(m>n)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int solve(int n,int k) {
	return (C(n,k)-C(n,k-1)+mod)%mod*(n-2*k+1)%mod;
}
signed main() {
	freopen("trade.in","r",stdin);
	freopen("trade.out","w",stdout);

	int opt,n,k;
	cin>>opt>>n;
	if(opt==1)cin>>k;
	init();
	if(opt==1) {
		cout<<solve(n,k)<<"\n";
	}
	else {
		int ans=0;
		int pw=1;
		for(int i=0;i<=n/2;i++) {
			ans=(ans+pw*solve(n,i)%mod)%mod;
			pw=pw*233%mod;
		}
		cout<<ans;
	}
}