#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=60+10;
int C[N][N];
int dp[N][N*N][N];
signed main() {
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=2*n+1;i++) {
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	dp[0][0][1]=1;
	for(int i=1;i<=2*n+1;i++)dp[i][C[i][2]][i+1]=1;
	for(int i=1;i<=2*n+1;i++)
		for(int j=0;j<=min(m,C[i][2]);j++)
			for(int k=2;k<=i+1;k++)
				for(int l=1;l<=2*n+1-i;l++)
					dp[i+l][j+C[l][2]][l-k+2]+=dp[i][j][k]*C[l-1][k-1];
	int ans=0;
	for(int i=1;i<=2*n+1;i++)
		for(int j=0;j<=min(m,C[i][2]);j++)
			for(int k=2;k<=i+1;k++)
				ans+=dp[i][j][k]*dp[2*n+1-i][m-j][k-1];
	cout<<ans;
}