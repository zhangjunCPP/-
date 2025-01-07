#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100005;
const int mod=998244353;
int dp[N],f[25],g[25][N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) g[1][i]=1;
	for(int i=1;i<=min(n+1,(long long)24);i++) {
		for(int j=1;j<=m;j++) {
			f[i]=(f[i]+g[i][j])%mod;
			for(int k=2;k*j<=m;k++) g[i+1][j*k]=(g[i+1][j*k]+g[i][j])%mod;
		}
	} 
	dp[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=min(i,(long long)24);j++){
			dp[i]=(dp[i]+(dp[i-j]*f[j])%mod*((j-1)&1?-1:1)+mod)%mod;
		}
	}
	cout<<dp[n]%mod<<endl;
	return 0;
}
