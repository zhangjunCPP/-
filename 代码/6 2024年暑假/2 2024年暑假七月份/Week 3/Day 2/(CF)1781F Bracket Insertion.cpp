#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500+10;
const int mod=998244353;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int C[N][N];
void init() {
	for(int i=0;i<N;i++) {
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int dp1[N][N],dp2[N][N];
signed main() {
	init();
	int n,p;
	cin>>n>>p;
	p=p*qpow(10000,mod-2)%mod;
	for(int i=0;i<=n;i++)dp1[0][i]=dp2[0][i]=1;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=n;j++) {
			for(int k=0;k<i;k++)dp1[i][j]=(dp1[i][j]+(p*dp1[k][j+1]+(1-p+mod)*(j?dp1[k][j-1]:0))%mod*C[i-1][k]%mod*dp2[i-k-1][j])%mod;
			for(int k=0;k<=i;k++)dp2[i][j]=(dp2[i][j]+C[i][k]*dp1[k][j]%mod*dp1[i-k][j]%mod)%mod;
		}
	}
	int ans=dp1[n][0];
	for(int i=1;i<=2*n;i+=2)ans=ans*qpow(i,mod-2)%mod;
	cout<<ans;
}