#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{
	int v,nex;
}a[N];
int fa[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	fa[v]=u;
}
int n,m,S;
int f(int x,int y) {return (x-1)*m+y;}
int other[N];

int dfn[N],tot;
int siz[N];
void dfs(int u) {
	dfn[u]=++tot;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v);
		siz[u]+=siz[v];
	}
}

//��ϯ��

struct node2{
	int ls,rs;
	int val,lazy;
}tree[N<<6];

void build(int &k,int l,int r){
	k=++tot;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(tree[k].ls,l,mid);
	build(tree[k].rs,mid+1,r);
	tree[k].val=tree[tree[k].ls].val+tree[tree[k].rs].val;
}
void update(int k,int l,int r,int val) {
	tree[k].lazy=val;
	tree[k].val=val*(r-l+1);
}
void pushdown(int k,int l,int r){
	if(tree[k].lazy){
		int mid=(l+r)>>1;
		node2 tmp=tree[tree[k].ls];
		tree[tree[k].ls=++tot]=tmp;
		update(tot,l,mid,tree[k].lazy);
		tmp=tree[tree[k].rs];
		tree[tree[k].rs=++tot]=tmp;
		update(tot,mid+1,r,tree[k].lazy);
		tree[k].lazy=0;
	}
}
int modify(int &k,int l,int r,int v,int x,int y,int val){
	if(y<l||x>r) return tree[k].val;
	k=++tot;
	pushdown(v,l,r);
	tree[k]=tree[v];
	if(x<=l&&r<=y){
		update(k,l,r,val);
		return tree[k].val;
	}
	int mid=(l+r)>>1;
	return tree[k].val=modify(tree[k].ls,l,mid,tree[v].ls,x,y,val)+modify(tree[k].rs,mid+1,r,tree[v].rs,x,y,val);
}
int query(int k,int l,int r,int x,int y){
	if(y<l||x>r) return 0;
	if(x<=l&&r<=y) return tree[k].val;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	return query(tree[k].ls,l,mid,x,y)+query(tree[k].rs,mid+1,r,x,y);
}
int root;
int rt[N];
int ask(int l,int r,int tim){
	return query(rt[tim],1,S,l,r);
}
void change(int l,int r,int val) {
	root++;
	modify(rt[root],1,S,rt[root-1],l,r,val);
}
int ans;
void dfs2(int u) {
	int tmp=root;
	if(other[u]) {
		int tmp2=ask(1,tot,tmp);
		change(dfn[other[u]],dfn[other[u]]+siz[other[u]]-1,1);
		ans+=(ask(1,tot,root)-tmp2)*siz[u];
	}
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		dfs2(v);
	}
	root=tmp;
}
signed main(){
	cin>>n>>m;
	S=n*m;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++){
			char ch;
			cin>>ch;
			if(ch=='L'&&j+2<=m) add(f(i,j+2),f(i,j));
			if(ch=='R'&&j-2>=1) add(f(i,j-2),f(i,j));
			if(ch=='U'&&i+2<=n) add(f(i+2,j),f(i,j));
			if(ch=='D'&&i-2>=1) add(f(i-2,j),f(i,j));
			if(ch=='L') other[f(i,j)]=f(i,j+1);
			if(ch=='R') other[f(i,j)]=f(i,j-1);
			if(ch=='U') other[f(i,j)]=f(i+1,j);
			if(ch=='D') other[f(i,j)]=f(i-1,j);
		}
	}
	for(int i=1;i<=S;i++) if(!fa[i]) dfs(i);
	build(rt[0],1,tot);
	for(int i=1;i<=S;i++) if(!fa[i]) dfs2(i);
	cout<<ans/2;
}
