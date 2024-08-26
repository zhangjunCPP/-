#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n,q;
int val[N];
int tim[N];
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N],fa[N],dep[N],son[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	dep[u]=dep[dad]+1;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[N],tot,idx[N];
int top[N];
void dfs2(int u){
	dfn[u]=++tot,idx[tot]=u;
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		dfs2(v);
	}
}
struct node2 {
	int Max,lazy,dep;
}tree[N];
int ls(int k){return k<<1;}
int rs(int k){return k<<1|1;}
void build(int k,int l,int r) {
	if(l==r) {
		tree[k].dep=dep[idx[l]]*2;
		tree[k].lazy=-1e18;
		return;
	}
	int mid=(l+r)>>1;
	build(ls(k),l,mid);
	build(rs(k),mid+1,r);
	tree[k].dep=max(tree[ls(k)].dep,tree[rs(k)].dep);
}
void update(int k,int val) {
	tree[k].Max=max(tree[k].Max,tree[k].dep+val);
	tree[k].lazy=max(tree[k].lazy,val);
}
void pushdown(int k) {
	update(ls(k),tree[k].lazy);
	update(rs(k),tree[k].lazy);
}
void pushup(int k) {tree[k].Max=max(tree[ls(k)].Max,tree[rs(k)].Max);}
void modify(int k,int l,int r,int x,int y,int val) {
	if(x<=l&&y>=r){update(k,val);return;}
	int mid=(l+r)>>1;
	pushdown(k);
	if(x<=mid)modify(ls(k),l,mid,x,y,val);
	if(y>mid)modify(rs(k),mid+1,r,x,y,val);
	pushup(k);
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&y>=r)return tree[k].Max;
	int mid=(l+r)>>1;
	pushdown(k);
	int ans=0;
	if(x<=mid)ans=max(ans,query(ls(k),l,mid,x,y));
	if(y>mid)ans=max(ans,query(rs(k),mid+1,r,x,y));
	return ans;
}
struct node3{
	int val,id;
	bool operator<(const node3&oth)const{return val>oth.val;}
};
set<node3> s;
void insert(int x) {
	int tmp=val[x]+tim[x]-dep[x];
	while(x) {
		modify(1,1,n,dfn[top[x]],dfn[x],tmp);
		x=fa[top[x]];
	}
}
int ask(int x,int t) {
	int tmp=dep[x];
	int ans=0;
	while(x) {
		ans=max(ans,query(1,1,n,dfn[top[x]],dfn[x])-t-tmp);
		x=fa[top[x]];
	}
	if(!s.empty())ans=max(ans,s.begin()->val);
	return ans;
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	build(1,1,n);
	for(int i=1;i<=n;i++)insert(i);
	while(q--) {
		int opt,t,x;
		cin>>opt>>t>>x;
		if(opt==1) {
			val[x]=max(0ll,val[x]+tim[x]-t);
			s.insert({val[x],x});
			tim[x]=-1;
		}
		else if(opt==2) {
			s.erase({val[x],x});
			tim[x]=t;
			insert(x);
		}
		else cout<<ask(x,t)<<"\n";
	}
}