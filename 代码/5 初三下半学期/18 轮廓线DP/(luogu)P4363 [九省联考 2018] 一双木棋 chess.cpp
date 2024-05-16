#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=15,INF=1e18;
int n,m;
int a[N][N],b[N][N];
int dp[1<<22];
int dfs(int s,int opt){
	if(dp[s]!=-1)return dp[s];
	if(opt)dp[s]=-INF;
	else dp[s]=INF;
	int x=n,y=0;
	for(int i=0;i<n+m-1;i++){
		if((s>>i)&1)x--;else y++;
		if(((s>>i)&3)!=1)continue;
		int now=s^(3<<i);
		if(opt)dp[s]=max(dp[s],dfs(now,opt^1)+a[x][y]);
		else dp[s]=min(dp[s],dfs(now,opt^1)-b[x][y]);
	}
	return dp[s];
}
signed main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>a[i][j];
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>b[i][j];
	memset(dp,-1,sizeof dp);
	dp[((1<<n)-1)<<m]=0;
	cout<<dfs((1<<n)-1,1);
}