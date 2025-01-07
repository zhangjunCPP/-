#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int col[N];
int siz[N],son[N],dep[N],fa[N];
void dfs1(int u,int dad){
	siz[u]=1;
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		col[v]=a[i].w;
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
		u=fa[x];
		x=top[u];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
bool vis[N];
int main(){
	int n;
	cin>>n;
	for(int i=2;i<=n;i++){
		int x,w;
		cin>>x>>w;
		add(x,i,w),add(i,x,w);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=1;k<=n;k++)vis[k]=false;
			int LCA=lca(i,j);
			int tmp=i;
			while(tmp!=LCA){
				vis[col[tmp]]=true;
				tmp=fa[tmp];
			}
			tmp=j;
			while(tmp!=LCA){
				vis[col[tmp]]=true;
				tmp=fa[tmp];
			}
			int sum=0;
			for(int k=1;k<=n;k++)sum+=vis[k];
			ans+=sum;
		}
	}
	cout<<ans;
}