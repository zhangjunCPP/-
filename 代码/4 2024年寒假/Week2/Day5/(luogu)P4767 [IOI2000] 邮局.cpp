#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int v[N];
int w[N][N];
int dp[N][N];
int opt[N][N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>v[i];
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)w[i][j]=w[i][j-1]+v[j]-v[(i+j)/2];
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int j=1;j<=m;j++){
		opt[n+1][j]=n;
		for(int i=n;i>=1;i--){
			for(int k=opt[i][j-1];k<=opt[i+1][j];k++){
				if(dp[i][j]>dp[k][j-1]+w[k+1][i]){
					dp[i][j]=dp[k][j-1]+w[k+1][i];
					opt[i][j]=k;
				}
			}
		}
	}
	cout<<dp[n][m];
	return 0;
}