#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
const int mod=1e9+7;
int dp[N][N];
int a[N];
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
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);

	int n,m,v;
	cin>>n>>m>>v;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=min(m,i);j++){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*a[i+1]%mod)%mod;
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*j%mod*v%mod)%mod;
			dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j]*(i+1)%mod*(m-j)%mod*v%mod)%mod;
		}
	}
	int ans=0;
	int inv=qpow(n,mod-2);
	for(int i=0;i<=min(n,m);i++){
		ans=(ans+dp[n][i]*qpow(inv,i)%mod)%mod;
	}
	cout<<ans%mod;

}