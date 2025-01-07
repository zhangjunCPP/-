#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=3e5+10;
int n,m;
int col[N];
struct node{int v,nex;}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	return;
}
int dep[N],siz[N],son[N],fa[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	siz[u]=1;
	dep[u]=dep[dad]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N],id[N],rev[N],tot;
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
	return;
}


struct node2{
	int sum;
	int lc,rc;
	int lazy;
	node2 operator+(const node2&oth){
		if(!lc)return oth;
		if(!oth.lc)return *this;
		node2 ans;
		ans.sum=sum+oth.sum-(rc==oth.lc);
		ans.lc=lc;
		ans.rc=oth.rc;
		ans.lazy=0;
		return ans;
	}
}tree[N*4];

void pushup(int k){
	tree[k].sum=tree[ls].sum+tree[rs].sum-(tree[ls].rc==tree[rs].lc);
	if(tree[ls].sum)tree[k].lc=tree[ls].lc;else tree[k].lc=tree[rs].lc;
	if(tree[rs].sum)tree[k].rc=tree[rs].rc;else tree[k].rc=tree[ls].rc;
	return;
}
void update(int k,int val){
	tree[k].sum=1;
	tree[k].lc=tree[k].rc=val;
	tree[k].lazy=val;
	return;
}
void pushdown(int k){
	if(tree[k].lazy){
		update(ls,tree[k].lazy);
		update(rs,tree[k].lazy);
		tree[k].lazy=0;
	}
}
void build(int k,int l,int r){
	if(l==r){
		tree[k]={1,col[rev[l]],col[rev[l]],0};
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k);
	return;
}
void change(int k,int l,int r,int x,int y,int val){
	if(l>y||r<x)return;
	if(x<=l&&r<=y){update(k,val);return;}
	int mid=(l+r)>>1;
	pushdown(k);
	change(ls,l,mid,x,y,val);
	change(rs,mid+1,r,x,y,val);
	pushup(k);
	return;
}
node2 query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[k];
	int mid=(l+r)>>1;
	pushdown(k);
	if(y<=mid)return query(ls,l,mid,x,y);
	if(x>mid)return query(rs,mid+1,r,x,y);
	return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
}
void modify(int x,int y,int val){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]){swap(fx,fy);swap(x,y);}
		change(1,1,n,id[fx],id[x],val);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	change(1,1,n,id[x],id[y],val);
	return;
}
int ask(int x,int y){
	node2 ans1,ans2;
	ans1.sum=ans2.sum=0;
	ans1.lc=ans2.lc=ans1.rc=ans2.rc=0;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]>dep[fy]){
			ans1=query(1,1,n,id[fx],id[x])+ans1;
			x=fa[fx];
			fx=top[x];
		}
		else{
			ans2=query(1,1,n,id[fy],id[y])+ans2;
			y=fa[fy];
			fy=top[y];
		}
	}
	if(dep[x]>dep[y])ans1=query(1,1,n,id[y],id[x])+ans1;
	else ans2=query(1,1,n,id[x],id[y])+ans2;
	swap(ans1.lc,ans1.rc);
	return (ans1+ans2).sum;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>col[i];
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
	while(m--){
		string opt;
		cin>>opt;
		if(opt=="C"){
			int u,v,w;
			cin>>u>>v>>w;
			modify(u,v,w);
		}
		if(opt=="Q"){
			int u,v;
			cin>>u>>v;
			cout<<ask(u,v)<<"\n";
		}
	}
	return 0;
}