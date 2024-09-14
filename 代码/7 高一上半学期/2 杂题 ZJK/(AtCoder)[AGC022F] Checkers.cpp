#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10;
const int mod=1e9+7;
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
const int lim=50;
int dp[N][N][N];
signed main() {
	init();
	int n;
	cin>>n;
	if(n==1){cout<<"1";return 0;}
	dp[1][1][0+lim]=dp[1][1][1+lim]=1;
	int ans=0;
	for(int i=2;i<=n;i++){
		for(int j=i;j<=n;j++)
			for(int k=j-n;k<=n-j;k++)
				for(int l=1;l<=j;l++)
					for(int m=0;m<=l;m++)
						if(llabs((k+m)*2-l)<=l)
							dp[i][j][k+lim]=(dp[i][j][k+lim]+dp[i-1][j-l][(k+m)*2-l+lim]*C(j,l)%mod*C(l,m)%mod)%mod;
		ans=(ans+dp[i][n][0+lim])%mod;
	}
	cout<<ans;
}
