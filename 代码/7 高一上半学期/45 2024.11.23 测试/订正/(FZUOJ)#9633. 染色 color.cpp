#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10,mod=998244353;
int n;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
}
int dp[N][N];
int calc(int i){return (dp[i][n]+dp[i][n-1]+dp[i][n-2])%mod*fac[i]%mod*fac[n-i]%mod;}
signed main(){
	init();
	cin>>n;
	if(n==3){cout<<"1";return 0;}
	n--;
	dp[0][0]=dp[1][1]=dp[1][2]=dp[1][3]=1;
	for(int i=2;i<=n;i++)for(int j=i;j<=min(n,3*i+1);j++)dp[i][j]=(dp[i-1][j-1]+dp[i-1][j-2]+dp[i-1][j-3])%mod;
	int ans=0;
	for(int i=1;i<=n;i++)ans=(ans+i*((calc(i)-calc(i-1)+mod)%mod)%mod)%mod;
	cout<<(ans*qpow(fac[n],mod-2)%mod+1)%mod;
}
