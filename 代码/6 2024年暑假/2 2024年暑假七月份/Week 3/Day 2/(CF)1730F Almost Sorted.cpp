#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int pos[N];
int dp[N][N];
int sum[N];
int main() {
	int n,k;
	cin>>n>>k;
	k++;
	for(int i=1;i<=n;i++) {
		int p;
		cin>>p;
		pos[p]=i;
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<=n;i++) {
		if(i)for(int j=1;j<=pos[i];j++)sum[j]++;
		for(int j=0;j<(1<<k);j+=2) {
			if(dp[i][j]!=0x3f3f3f3f) {
				for(int l=1;l<=k&&i+l<=n;l++) {
					if(!((j>>(l-1))&1)) {
						int tot=sum[pos[i+l]+1];
						int tmp1=i,tmp2=j|(1<<(l-1));
						while(tmp2&1)tmp1++,tmp2>>=1;
						for(int m=1;m<=k;m++)if(pos[i+m]>pos[i+l]&&((j>>(m-1))&1))tot++;
						dp[tmp1][tmp2]=min(dp[tmp1][tmp2],dp[i][j]+tot);
					}
				}
			}
		}
	}
	cout<<dp[n][0];
}