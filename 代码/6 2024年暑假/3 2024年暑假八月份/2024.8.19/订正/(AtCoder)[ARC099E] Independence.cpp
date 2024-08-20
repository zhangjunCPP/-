#include <bits/stdc++.h>
using namespace std;
const int N=5000+10,INF=1e9;
struct node {
	int v,nex;
}a[N*N*2];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis[N];
int col[N],tot[2];
void dfs(int u,int color) {
	vis[u]=true;
	col[u]=color;
	tot[color]++;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(!vis[v])dfs(v,color^1);
		else if(col[v]==color){puts("-1");exit(0);}
	}
}
bitset<N>dp;
bool mp[N][N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){int u,v;cin>>u>>v;mp[u][v]=mp[v][u]=true;}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(!mp[i][j]&&i!=j)add(i,j);
	dp[0]=1;
	for(int i=1;i<=n;i++) {
		if(!vis[i]) {
			tot[0]=tot[1]=0;
			dfs(i,0);
			dp=(dp<<tot[0])|(dp<<tot[1]);
		}
	}
	int ans=INF;
	for(int i=1;i<=n;i++)if(dp[i])ans=min(ans,i*(i-1)+(n-i)*(n-i-1));
	cout<<ans/2;
}