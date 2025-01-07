#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10,mod=998244353;
int dp[N][N];
int a[N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		if(a[i])for(int j=1;j<=min(n,m+1);j++)dp[i][j]=dp[i-1][j-1];
		else for(int j=1;j<=min(n,m+1);j++)dp[i][j]=(dp[i-1][j]*j%mod+dp[i-1][j-1]*(m+1-j)%mod)%mod;
	}
	int ans=0;
	for(int i=1;i<=min(n,m+1);i++)ans=(ans+dp[n][i])%mod;
	cout<<ans;
}