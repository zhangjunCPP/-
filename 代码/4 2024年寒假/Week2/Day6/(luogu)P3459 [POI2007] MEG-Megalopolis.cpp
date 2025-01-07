#include <bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=5e6+10;
const int INF=0x3f3f3f3f;
int n;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int val[N];
int fa[N],siz[N],son[N],dep[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	siz[u]=1;
	dep[u]=dep[dad]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		val[v]=1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N];
int id[N],tot,rev[N];
void dfs2(int u){
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		id[v]=++tot;
		rev[id[v]]=v;
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		id[v]=++tot;
		rev[id[v]]=v;
		dfs2(v);
	}
}

int tree[N];
void pushup(int k){tree[k]=tree[ls]+tree[rs];}
void build(int k,int l,int r){
	if(l==r){
		tree[k]=val[rev[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k);
}
void change1(int k,int l,int r,int x,int y){ //单点修改
	if(l==r){
		tree[k]=y;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change1(ls,l,mid,x,y);
	else change1(rs,mid+1,r,x,y);
	pushup(k);
}
int ans;
void query(int k,int l,int r,int x,int y){//区间查询
	if(l>y||r<x)return;
	if(x<=l&&y>=r){
		ans+=tree[k];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)query(ls,l,mid,x,y);
	if(y>mid)query(rs,mid+1,r,x,y);
}
void ask(int x,int y){//树上查询
	ans=0;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]){swap(fx,fy);swap(x,y);}
		query(1,1,n,id[fx],id[x]);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(x!=y)query(1,1,n,id[x]+1,id[y]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	id[1]=++tot;
	rev[id[1]]=1;
	dfs2(1);
	build(1,1,n);
	int m;
	cin>>m;
	m=n+m-1;
	while(m--){
		string opt;
		cin>>opt;
		if(opt=="A"){
			int u,v;
			cin>>u>>v;
			if(dep[u]<dep[v])swap(u,v);
			change1(1,1,n,id[u],0);
		}
		else{
			int u;
			cin>>u;
			ask(1,u);
			cout<<ans<<"\n";
		}
	}
}