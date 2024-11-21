#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int n,q;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int fa[N][20];
int siz[N],son[N],dep[N];
int sum[N];
void dfs1(int u,int dad){
	siz[u]=1;
	dep[u]=dep[dad]+1;
	fa[u][0]=dad;
	for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
		sum[u]=(sum[u]+siz[v]*siz[v]%mod)%mod%mod;
	}
}
int top[N];
void dfs2(int u){
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v]) continue;
		top[v]=v;
		dfs2(v);
	}
}
int lca(int u,int v){
	int x=top[u],y=top[v];
	while(x!=y){
		if(dep[x]<dep[y]){ swap(x,y), swap(u,v);}
		u=fa[x][0];
		x=top[u];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
int get(int u,int v){
	for(int i=19;i>=0;i--)if(dep[fa[u][i]]>dep[v])u=fa[u][i];
	return u;
}
int calc(int x,int y){
	if(dep[x]>dep[y])swap(x,y);
	int LCA=lca(x,y);
	int ans;
	if(x==LCA){
		int son=get(y,x);
		ans=(siz[y]*siz[y]%mod-sum[y]+mod)%mod*((n-siz[son])*(n-siz[son])%mod-sum[x]+siz[son]*siz[son]%mod-(n-siz[x])*(n-siz[x])%mod+mod)%mod;
	}
	else ans=(siz[x]*siz[x]%mod-sum[x]+mod)%mod*(siz[y]*siz[y]%mod-sum[y]+mod)%mod;
	return ans*4%mod;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	while(q--){
		int x,y;
		cin>>x>>y;
		cout<<calc(x,y)<<"\n";
	}
}