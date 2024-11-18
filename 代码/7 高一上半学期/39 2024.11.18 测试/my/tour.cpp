#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244353;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N],son[N],dep[N],fa[N];
void dfs1(int u,int dad){
	siz[u]=1;
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
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
		if(dep[x]<dep[y]){swap(x,y), swap(u,v);}
		u=fa[x];
		x=top[u];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
int dis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
int val[N];
int tmp_k,tmp_b;
void dfs_add(int u,int dad){
	val[u]=(tmp_k*val[u]%mod+tmp_b)%mod;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs_add(v,u);
	}
}
signed main(){
	int sub,n,q;
	cin>>sub>>n>>q;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++)cin>>val[i];
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int x;
			cin>>x;
			cout<<val[x]%mod<<"\n";
		}
		else if(opt==2){
			int x,y,k,b;
			cin>>x>>y>>k>>b;
			int LCA=lca(x,y);
			while(x!=LCA){
				val[x]=(k*val[x]%mod+b)%mod;
				x=fa[x];
			}
			while(y!=LCA){
				val[y]=(k*val[y]%mod+b)%mod;
				y=fa[y];
			}
			val[LCA]=(k*val[LCA]%mod+b)%mod;
		}
		else if(opt==3){
			int x,k,b;
			cin>>x>>k>>b;
			tmp_k=k,tmp_b=b;
			dfs_add(x,fa[x]);
		}
		else{
			int x,r,k,b;
			cin>>x>>r>>k>>b;
			for(int i=1;i<=n;i++)if(dis(i,x)<=r)val[i]=(k*val[i]%mod+b)%mod;
		}
	}
}