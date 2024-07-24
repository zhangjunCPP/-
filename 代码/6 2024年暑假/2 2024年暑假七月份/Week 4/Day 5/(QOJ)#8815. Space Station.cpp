#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10;
const int mod=998244353;
int fac[N],invfac[N],inv[N];
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
	fac[1]=invfac[1]=inv[1]=1;
	fac[0]=invfac[0]=inv[0]=1;
	for(int i=2;i<N;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	invfac[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>=2;i--)invfac[i]=invfac[i+1]*(i+1)%mod;
}
int inv_C(int n,int m) {return invfac[n]*fac[m]%mod*fac[n-m]%mod;}
int a[N];
int dp[N][2*N*N];
signed main() {
	init();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	int sum=0;
	dp[0][0]=1;
	for(int i=1;i<=n;i++) {
		sum+=a[i];
		for(int j=i;j>=1;j--)for(int k=min(sum,200*j);k>=a[i];k--)dp[j][k]=(dp[j][k]+dp[j-1][k-a[i]])%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=sum;j++)
			ans=(ans+dp[i][j]*inv_C(n,i)%mod*min(j,i*m)%mod*inv[i]%mod)%mod;
	cout<<ans;
}