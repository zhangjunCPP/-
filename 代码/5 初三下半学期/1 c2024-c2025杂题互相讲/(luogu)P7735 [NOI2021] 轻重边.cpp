#include <bits/stdc++.h>

using namespace std;
const int N=1e6+10;
int n,m;
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
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int id[N],tot;
int top[N];
void dfs2(int u){
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		id[v]=++tot;
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		id[v]=++tot;
		dfs2(v);
	}
}
struct node2{
	int lc=0,rc=0;
	int sum=0;
	int lazy=0;
	node2 operator+(const node2&oth)const{
		if(!lc)return oth;
		if(!oth.lc)return *this;
		node2 ans;
		ans.sum=sum+oth.sum+(rc==oth.lc);
		ans.lc=lc;
		ans.rc=oth.rc;
		ans.lazy=0;
		return ans;
	}
}tree[N];
void build(int k,int l,int r){
	if(l==r){
		tree[k]={l,l,0,0};
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=tree[k<<1]+tree[k<<1|1];
}
void update(int k,int l,int r,int val){
	tree[k].lc=tree[k].rc=val;
	tree[k].lazy=val;
	tree[k].sum=r-l;
}
void pushdown(int k,int l,int r){
	if(tree[k].lazy){
		int mid=(l+r)>>1;
		update(k<<1,l,mid,tree[k].lazy);
		update(k<<1|1,mid+1,r,tree[k].lazy);
		tree[k].lazy=0;
	}
}
void modify(int k,int l,int r,int x,int y,int val){
	if(x>r||y<l)return;
	if(x<=l&&y>=r){
		update(k,l,r,val);
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify(k<<1,l,mid,x,y,val);
	if(y>mid)modify(k<<1|1,mid+1,r,x,y,val);
	tree[k]=tree[k<<1]+tree[k<<1|1];
}
node2 query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k];
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x>mid)return query(k<<1|1,mid+1,r,x,y);
	if(y<=mid)return query(k<<1,l,mid,x,y);
	return query(k<<1,l,mid,x,mid)+query(k<<1|1,mid+1,r,mid+1,y);
}
void change(int x,int y,int val){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]){swap(x,y);swap(fx,fy);}
		modify(1,1,n,id[fx],id[x],val);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	modify(1,1,n,id[x],id[y],val);
}
int ask(int x,int y){
	node2 ansx,ansy;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]>dep[fy]){
			ansx=query(1,1,n,id[fx],id[x])+ansx;
			x=fa[fx];
			fx=top[x];
		}
		else{
			ansy=query(1,1,n,id[fy],id[y])+ansy;
			y=fa[fy];
			fy=top[y];
		}
	}
	if(dep[x]>dep[y])ansx= query(1,1,n,id[y],id[x])+ansx;
	else ansy= query(1,1,n,id[x],id[y])+ansy;
	swap(ansx.lc,ansx.rc);
	return (ansx+ansy).sum;
}
void init(){
	memset(first,0,sizeof first);
	memset(son,0,sizeof son);
	memset(top,0,sizeof top);
	cnt=0;
	tot=0;
}

void solve(){
	init();
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	id[1]=++tot;
	dfs2(1);
	build(1,1,n);
	int tmp=n;
	while(m--){
		int opt,u,v;
		cin>>opt>>u>>v;
		if(opt==1)change(u,v,++tmp);
		else cout<<ask(u,v)<<"\n";
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}