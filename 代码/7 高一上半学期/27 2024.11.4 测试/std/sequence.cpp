#include<bits/stdc++.h>
using namespace std;
int N,a[1050000],dp[2][3][3];
int main() {
	scanf("%d",&N);
	for (int i=1;i<=N;i++) {
		scanf("%d",&a[i]);
	}
	memset(dp,0,sizeof(dp));
	dp[0][a[1]%3][0]=1;
	for (int i=2;i<=N;i++) {
		for (int j=0;j<3;j++) {
			for (int k=0;k<3;k++) {
				int x=(a[i]+3-j)%3;
				if (x>=k) dp[1][a[i]%3][x]=max(dp[1][a[i]%3][x],dp[0][j][k]+1);
			}
		}
		for (int j=0;j<3;j++) {
			for (int k=0;k<3;k++) {
				dp[0][j][k]=max(dp[0][j][k],dp[1][j][k]);
				dp[1][j][k]=0;
			}
		}
	}
	int ans=0;
	for (int j=0;j<3;j++) {
		for (int k=0;k<3;k++) {
			ans=max(ans,dp[0][j][k]);
		}
	}
	printf("%d\n",ans);
	return 0;
}