#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7;
struct node{
	int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dfn[N],low[N],tot;
bool cut[N];
void Tarjan(int u,int edge){
	dfn[u]=low[u]=++tot;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!dfn[v]){
			Tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])cut[i]=cut[i^1]=true;
		}
		else if(i!=(edge^1))low[u]=min(low[u],dfn[v]);
	}
}
int col[N],ecc;
int sum[N];
void dfs(int u){
	col[u]=ecc;
	sum[ecc]++;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(col[v]||cut[i])continue;
		dfs(v);
	}
}
vector<int> G[N];
int fa[N],siz[N],son[N],dep[N];
int dis[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	siz[u]=1;
	dep[u]=dep[dad]+1;
	dis[u]=dis[dad]+(sum[u]>1);
	for(int v:G[u]){
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N];
void dfs2(int u){
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
	}
	for(int v:G[u]){
		if(top[v])continue;
		top[v]=v;
		dfs2(v);
	}
}
int lca(int x,int y){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int u[N],v[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	for(int i=1;i<=n;i++)if(!col[i])ecc++,dfs(i);
	for(int i=1;i<=m;i++)if(col[u[i]]!=col[v[i]])G[col[u[i]]].push_back(col[v[i]]),G[col[v[i]]].push_back(col[u[i]]);
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	int q;
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		x=col[x],y=col[y];
		int LCA=lca(x,y);
		cout<<qpow(2,dis[x]+dis[y]-2*dis[LCA]+(sum[LCA]>1))<<"\n";
	}
}