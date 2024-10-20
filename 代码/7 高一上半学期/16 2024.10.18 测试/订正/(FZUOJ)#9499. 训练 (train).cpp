#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=30+10;
const int mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int a[N],sum[N];
int dp[N][N][N*N];
int inv[N];
int f[N*N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,D;
	cin>>n>>D;
	for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
	if(sum[n]>D){cout<<0;return 0;}
	inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=0;i<=sum[n];i++){
		f[i][0]=1;
		int x=D-i;
		for(int j=1;j<N;j++,x--)f[i][j]=f[i][j-1]*inv[j]%mod*x%mod;
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int k=0;k<=sum[i];k++){
				dp[i][j][k]=dp[i-1][j][k];
				if(j)for(int l=0;l<=min(a[i]-1,k);l++)dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][k-l]*f[k-l][l]%mod)%mod;
			}
	int ans=qpow(n,D);
	for(int i=1;i<=n;i++)for(int j=0;j<=sum[n];j++)ans=(ans+(i&1?-1:1)*dp[n][i][j]*qpow(n-i,D-j)%mod+mod)%mod;
	cout<<ans;
	return 0;
}