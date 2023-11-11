#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
int val[N];
void add(int u,int v,int w) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	val[cnt]=w;
}
int dep[N],siz[N],fa[N];
int son[N];
int dfs[N],tot;  //Å·À­Ðò 
void dfs1(int u,int dad){
	dep[u]=dep[dad]+1;
	siz[u]=1;
	fa[u]=dad;
	dfs[++tot]=u;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
	dfs[++tot]=u;
}
int top[N];
int id[N],sum;
void dfs2(int u){
	if(son[u]) {
		int v=son[u];
		top[v]=top[u];
		id[v]=++sum;
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(id[v]) continue;
		top[v]=v;
		id[v]=++sum;
		dfs2(v);
	}
}
int lca(int x,int y){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]) {
			swap(x,y);
			swap(fx,fy);
		}
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
}
int l[N],r[N];
int dis[N];
void update(int u,int dad) {
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dis[v]=dis[u]+val[i];
		update(v,u);
	}
}
bool vis[N];
int getdis(int x,int y){
	int LCA=lca(x,y);
	return dis[x]+dis[y]-2*dis[LCA];
}
int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
} 
signed main(){
	freopen("release.in","r",stdin);
	freopen("release.out","w",stdout);
	int n,m;
	n=read();m=read();
	for(int i=1;i<n;i++) {
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);
		add(v,u,w);
	}	
	update(1,0);
	dfs1(1,0);
	top[1]=1;
	id[1]=++sum;
	dfs2(1);
	for(int i=1;i<=tot;i++) {
		if(!l[dfs[i]]) l[dfs[i]]=i;
		r[dfs[i]]=i;
	}
	while(m--) {
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1) {
			val[2*x-1]=val[2*x]=y;
			update(1,0);
		}
		else {
			int ans=0;
			for(int i=1;i<=n;i++) vis[i]=false;
			for(int i=l[y];i<=r[y];i++) {
				if(!vis[dfs[i]]) {
					vis[dfs[i]]=true;
					ans+=getdis(x,dfs[i]);
				}
			}
			cout<<ans<<"\n";
		}
	}
} 
