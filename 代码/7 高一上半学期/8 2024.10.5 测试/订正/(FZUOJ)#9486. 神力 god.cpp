#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=5000+10;

int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int a[N];
int dp[N][N*2];
signed main(){
	int n,p;
	cin>>n>>p;
	p=p*qpow(100,mod-2)%mod;
	int q=(1-p+mod)%mod;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[n+1][0+n+1]=1;
	for(int i=n;i;i--){
		for(int j=-n+n+1;j<=n+n+1;j++)dp[i][j]=(dp[i+1][j]*p%mod+dp[i+1][j+a[i]]*q%mod)%mod;		
		dp[i][0+n+1]=1;
	}
	for(int i=n+n+1;i>=-n+n+1;i--)cout<<dp[1][i]<<" ";
}