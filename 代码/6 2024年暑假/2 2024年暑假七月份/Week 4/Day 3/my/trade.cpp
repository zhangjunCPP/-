#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=300+10,mod=998244353;
int dp[2][N*2][N],lim=300;
int way[N*2];
signed main() {
	freopen("trade.in","r",stdin);
	freopen("trade.out","w",stdout);
	int opt;
	cin>>opt;
	int _n,_k=-1;
	if(opt==1)cin>>_n>>_k;
	else cin>>_n;
	dp[1][0+lim][0]=2;
	dp[1][-1+lim][1]=dp[1][-2+lim][1]=1;
	for(int n=2;n<=_n;n++) {
		for(int k=0;k<=n/2+lim;k++) {
			dp[n&1][k][0]=(dp[(n-1)&1][k][0]*2+dp[(n-1)&1][k-1][1]+dp[(n-1)&1][k-2][1])%mod;
			for(int i=1;i<=n;i++) {
				dp[n&1][k][i]=dp[(n-1)&1][k][i]*2%mod;
				if(k>=1)dp[n&1][k][i]+=dp[(n-1)&1][k-1][i+1];
				if(k>=2)dp[n&1][k][i]+=dp[(n-1)&1][k-2][i+1];
				dp[n&1][k][i]+=dp[(n-1)&1][k+1][i-1]+dp[(n-1)&1][k+2][i-1];
				dp[n&1][k][i]%=mod;
			}
		}
	}
	if(opt==1) {
		int ans=0;
		for(int i=0;i<=_n;i++)ans=(ans+dp[_n&1][_k+lim][i])%mod;
		cout<<ans;
	}
	else {
		for(int k=lim;k<=_n/2+lim;k++)for(int i=0;i<=_n;i++)way[k]=(way[k]+dp[_n&1][k][i])%mod;
		int ans=0,pw=1;
		for(int k=lim;k<=_n/2+lim;k++)ans=(ans+pw*way[k%mod])%mod,pw=pw*233%mod;
		cout<<ans;
	}
}