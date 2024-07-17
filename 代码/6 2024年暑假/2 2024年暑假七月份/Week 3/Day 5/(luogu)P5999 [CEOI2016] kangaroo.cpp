#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
const int mod=1e9+7;
int dp[N][N];
signed main() {
	int n,s,t;
	cin>>n>>s>>t;
	dp[1][1]=1;
	for(int i=2;i<=n;i++) {
		for(int j=1;j<=i;j++) {
			if(i!=s&&i!=t)dp[i][j]=(j*dp[i-1][j+1]%mod+(j-(i>s)-(i>t))*dp[i-1][j-1]%mod)%mod;
			else dp[i][j]=(dp[i-1][j-1]+dp[i-1][j])%mod;
		}
	}
	cout<<dp[n][1]%mod;
}