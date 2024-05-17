#include <bits/stdc++.h>
using namespace std;
const int N=25,INF=1e9;
int n;
string s[N];
int w[N][N];
int dp[1<<N];
struct node{int val,id,col;};
int dfs(int S){
	if(dp[S]!=-1)return dp[S];
	dp[S]=INF;
	int cnt=0;
	node tmp[N];
	int x=n-1,y=0;
	for(int i=0;i<2*n-1;i++){
		if(((S>>i)&3)==1){
			if(s[x][y]=='.')return dp[S]=dfs(S^(3<<i));
			if(s[x][y]=='B')tmp[++cnt]={w[x][y],i,1};
			if(s[x][y]=='W')tmp[++cnt]={w[x][y],i,0};
		}
		if((S>>i)&1)x--;
		else y++;
	}
	for(int i=1;i<=cnt;i++){
		dp[S]=min(dp[S],dfs(S^(3<<tmp[i].id))+tmp[i].val);
		for(int j=1;j<i;j++)if(tmp[i].col!=tmp[j].col)dp[S]=min(dp[S],dfs(S^(3<<tmp[i].id)^(3<<tmp[j].id))+abs(tmp[i].val-tmp[j].val));
	}
	return dp[S];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=n-1;i>=0;i--)cin>>s[i];
	for(int i=n-1;i>=0;i--)for(int j=0;j<n;j++)cin>>w[i][j];
	memset(dp,-1,sizeof dp);
	dp[((1<<n)-1)<<n]=0;
	cout<<dfs((1<<n)-1);
}