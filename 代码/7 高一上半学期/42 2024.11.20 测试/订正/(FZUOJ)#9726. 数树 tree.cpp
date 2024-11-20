#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp[N][4][4],g[4][4];
void dfs(int u,int fa){
	dp[u][0][0]=dp[u][0][1]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		for(int x=0;x<=3;x++){
			for(int y=0;x+y<=3;y++){
				for(int l=0;l<=3;l++)g[x+y][l]=(g[x+y][l]+dp[u][x][l]*(dp[v][y][0]+dp[v][y][3])%mod)%mod;
				if(x+y+1<=3)for(int l=1;l<=2;l++)for(int k=1;k<=2;k++)g[x+y+1][3]=(g[x+y+1][3]+dp[u][x][l]*dp[v][y][k]%mod)%mod;
				g[x+y][2]=(g[x+y][2]+dp[u][x][1]*(dp[v][y][1]+dp[v][y][2])%mod)%mod;
			}
		}
		for(int x=0;x<=3;x++)for(int j=0;j<=3;j++)dp[u][x][j]=g[x][j],g[x][j]=0;
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<(dp[1][3][0]+dp[1][3][3])%mod;
}