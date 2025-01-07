#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[5005][5005];
int s1[50005],s2[50005];
int mod;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
signed main(){
	int n;
	cin>>n>>mod;
	dp[1][1]=1;
	s1[2]=1;

	for(int i=2;i<=n;i++){
		for(int j=1;j<=n*2;j++)s2[j]=(s2[j-1]+s1[j])%mod;
		dp[i][i]=qpow(2,i-2);
		for(int j=1;j*2<i;j++){
			dp[i][j]=(dp[j][j]*s2[i-j*2-1])%mod;
			dp[i][i]=(dp[i][i]-dp[i][j]+mod)%mod;
		}
		for(int j=1;j<=i;j++)s1[i+j]=(s1[i+j]+dp[i][j])%mod;
	}
	cout<<dp[n][n]%mod;
}