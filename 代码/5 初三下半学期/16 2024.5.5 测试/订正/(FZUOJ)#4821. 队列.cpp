#include <bits/stdc++.h>
using namespace std;
const int N=750,M=3010;
int n,m;
int h[N][N];
int tmp[N];
void solve1(){
	for(int i=1;i<m;i++)if(h[1][i]>=h[1][i+1]){cout<<"-1\n";return;}
	int ans=0;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++)tmp[j]=h[i][j]-h[1][j];
		sort(tmp+1,tmp+m+1);
		int tmp2=tmp[(m+1)/2];
		for(int j=1;j<=m;j++)ans+=abs(tmp[j]-tmp2);
	}
	cout<<ans<<"\n";
}
int dp[N][M];
int sum[M];
void solve2(){
	tmp[1]=0;
	for(int i=2;i<=n;i++)tmp[i]=h[i][1]-h[1][1];
	dp[1][h[1][1]]=0;
	for(int i=0;i<h[1][1];i++)dp[1][i]=0x3f3f3f3f;
	for(int i=2;i<=m;i++){
		for(int j=h[1][1]+i-1;j<=2000;j++){
			sum[j]=0;
			for(int k=1;k<=n;k++)sum[j]+=abs(j+tmp[k]-h[k][i]);
		}
		for(int j=0;j<=2000;j++){
			if(j==0)dp[i][j]=0x3f3f3f3f;
			else dp[i][j]=min(dp[i-1][j-1]+sum[j],dp[i][j-1]);
		}
	}
	cout<<dp[m][2000];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>h[i][j],h[i][j]+=1000;
	solve1();
	solve2();
	return 0;
}