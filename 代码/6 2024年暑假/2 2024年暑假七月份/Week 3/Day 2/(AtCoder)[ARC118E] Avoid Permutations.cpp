#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200+10;
const int mod=998244353;
int a[N],b[N];
int dp[N][N][N][2][2];
int fac[N];
signed main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)b[i]=-1;
	int m=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>0)b[a[i]]=i;
		else m++;
	}
	fac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
	dp[0][0][0][1][1]=1;
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=n+1;j++)
			for(int k=0;k<=m;k++)
				for(int l=0;l<2;l++)
					for(int p=0;p<2;p++){
						if(i<=n){
							dp[i+1][j][k][a[i+1]>=0][p]=(dp[i+1][j][k][a[i+1]>=0][p]+dp[i][j][k][l][p])%mod;
							if(a[i+1]==j&&j)dp[i+1][j][k][1][1]=(dp[i+1][j][k][1][1]-dp[i][j][k][l][p]+mod)%mod;
							if(a[i+1]<0&&!p)dp[i+1][j][k+1][1][1]=(dp[i+1][j][k+1][1][1]-dp[i][j][k][l][p]+mod)%mod;
						}
						if(j<=n){
							dp[i][j+1][k][l][b[j+1]>=0]=(dp[i][j+1][k][l][b[j+1]>=0]+dp[i][j][k][l][p])%mod;
							if(b[j+1]==i&&i)dp[i][j+1][k][1][1]=(dp[i][j+1][k][1][1]-dp[i][j][k][l][p]+mod)%mod;
							if(b[j+1]<0&&!l)dp[i][j+1][k+1][1][1]=(dp[i][j+1][k+1][1][1]-dp[i][j][k][l][p]+mod)%mod;
						}
					}
	int ans=0;
	for(int i=0;i<=m;i++)ans=(ans+dp[n+1][n+1][i][1][1]*fac[m-i]%mod)%mod;
	cout<<ans;
	return 0;
}