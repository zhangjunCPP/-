#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=5e5+10;
int n,q;
struct node {
	int v,nex;
}a[N*2];
int first[N],cnt;
int col[N];
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N],siz[N],son[N],fa[N];
void dfs1(int u,int dad) {
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex) {
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
}


struct node2{
	int sum;
	int lc,rc;
	int Max;
	node2 operator+(const node2&oth)const{
		if(!lc)return oth;
		if(!oth.lc)return *this;
		node2 ans;
		ans.sum=sum+oth.sum-(rc==oth.lc);
		ans.lc=lc;
		ans.rc=oth.rc;
		ans.Max=max(Max,oth.Max);
		return ans;
	}
}tree[N*4];

void pushup(int k){
	tree[k].sum=tree[ls].sum+tree[rs].sum-(tree[ls].rc==tree[rs].lc);
	if(tree[ls].sum)tree[k].lc=tree[ls].lc;else tree[k].lc=tree[rs].lc;
	if(tree[rs].sum)tree[k].rc=tree[rs].rc;else tree[k].rc=tree[ls].rc;
	tree[k].Max=max(tree[ls].Max,tree[rs].Max);
}
void update(int k,int val){
	tree[k].sum=1;
	tree[k].lc=tree[k].rc=val;
	tree[k].Max=val;
}
void build(int k,int l,int r){
	if(l==r){
		tree[k]={1,col[rev[l]],col[rev[l]],col[rev[l]]};
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k);
}
void change(int k,int l,int r,int x,int y,int val){
	if(l>y||r<x)return;
	if(x<=l&&r<=y){update(k,val);return;}
	int mid=(l+r)>>1;
	change(ls,l,mid,x,y,val);
	change(rs,mid+1,r,x,y,val);
	pushup(k);
}
node2 query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[k];
	int mid=(l+r)>>1;
	if(y<=mid)return query(ls,l,mid,x,y);
	if(x>mid)return query(rs,mid+1,r,x,y);
	return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
}
void modify(int x,int val){
	change(1,1,n,id[x],id[x],val);
}
pair<int,int> ask(int x,int y){
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
	node2 tmp=ans1+ans2;
	return {tmp.sum,tmp.Max};
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
int dis(int u,int v) {
	// cout<<"dis "<<u<<" "<<v<<": "<<dep[u]<<" "<<dep[v]<<" "<<dep[lca(u,v)]<<"\n";
	return dep[u]+dep[v]-2*dep[lca(u,v)]+1;
}
void clear() {
	memset(first,0,sizeof first);
	cnt=0;
	memset(dep,0,sizeof dep);
	memset(top,0,sizeof top);
	// memset(fa,0,sizeof fa);
	// memset(id,0,sizeof id);
	// memset(rev,0,sizeof rev);
	// memset(tree,0,sizeof tree);
	memset(son,0,sizeof son);
	// memset(a,0,sizeof a);
	// memset(siz,0,sizeof siz);
	// memset(col,0,sizeof col);
	tot=0;
}
void solve() {
	clear();
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
	id[1]=++tot;
	rev[id[1]]=1;
	dfs2(1);
	build(1,1,n);
	while(q--){
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1) {
			auto it=ask(x,y);
			if(it.first!=dis(x,y))cout<<"No\n";
			else {
				if(it.second!=dis(x,y))cout<<"No\n";
				else cout<<"Yes\n";
			}
		}
		else modify(x,y);
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
/*
 *一个区间为排列的充要条件：区间权值种类为len，区间权值最大值为len
 *所以我们只需要为维护出区间权值种类，和区间最大值
 *最大值是好维护的，但区间种类怎么维护？
 *线段树存下每个结点的权值，然后树剖，线段树合并？
 *不太能做的样子
 *我记得之前做过统计树上两点间权值种类的题？
 *小小T1，直接拿下
 */