#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int fa[N][20],dep[N];
void dfs(int u,int dad){
	fa[u][0]=dad;
	dep[u]=dep[dad]+1;
	for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	}
	if(x==y) return x;
	for(int i=19;i>=0;i--){
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int dis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
int p[N];

int boss[N];
int find(int x){
	if(x!=boss[x])return  boss[x]=find(boss[x]);
	return boss[x];
}
int dp[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) boss[i]=i;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		u=p[u],v=p[v];
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int u=1;u<=n;u++){
		for(int i=first[u];i;i=a[i].nex){
			int v=find(a[i].v);
			if(v<u) boss[v]=u,dp[u]=max(dp[u],dp[v]+dis(u,v));
		}
	}
	cout<<dp[n]<<"\n";
}