#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]=node{v,first[u]};
	first[u]=cnt;
}

int siz[N],son[N],depth[N],fa[N];
void dfs1(int u,int dad){
	siz[u]=1;
	depth[u]=depth[dad]+1;
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
		if(depth[x]<depth[y]){ swap(x,y), swap(u,v);}
		u=fa[x];
		x=top[u];
	}
	if(depth[u]>depth[v]) swap(u,v);
	return u;
}
int n,q;
int col[N];
map<int,bool> mp[N];
void solve() {
	for(int i=1;i<=n;i++)mp[i].clear();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(col[i]!=col[j])continue;
			// cout<<i<<" "<<j<<"\n";
			int LCA=lca(i,j);
			int tmp=i;
			while(tmp!=LCA) {
				mp[col[i]][tmp]=true;
				tmp=fa[tmp];
			}
			tmp=j;
			while(tmp!=LCA) {
				mp[col[i]][tmp]=true;
				tmp=fa[tmp];
			}
			mp[col[i]][LCA]=true;
		}
	}
}
int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>col[i];
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	solve();
	// for(int i=1;i<=n;i++) {
	// 	cout<<"col="<<i<<":\n";
	// 	for(int j=1;j<=n;j++)cout<<mp[i][j]<<" ";
	// 	cout<<"\n";
	// }
	while(q--) {
		int opt,u,v;
		cin>>opt>>u>>v;
		if(opt==1) {
			col[u]=v;
			solve();
		}
		else {
			int LCA=lca(u,v);
			int ans=0;
			for(int i=1;i<=n;i++) {
				int tmp=u;
				while(tmp!=LCA) {
					if(mp[i][tmp]){ans++;goto here;}
					tmp=fa[tmp];
				}
				tmp=v;
				while(tmp!=LCA) {
					if(mp[i][tmp]){ans++;goto here;}
					tmp=fa[tmp];
				}
				if(mp[i][LCA])ans++;
				here:;
			}
			cout<<ans<<"\n";
		}
	}

}