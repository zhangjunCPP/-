#include"catdog.h"
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;
struct matrix{
	int a[2][2];
	matrix(){memset(a,0x3f,sizeof a);}
	matrix operator*(const matrix&oth)const{
		matrix ans;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)ans.a[i][j]=min(ans.a[i][j],a[i][k]+oth.a[k][j]);
		return ans;		
	}
}mat[N];
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int f[N][2],g[N][2];
int dep[N],siz[N],son[N],fa[N];
void dfs1(int u,int dad){
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N];
int dfn[N],idx[N],tot;
int last[N];
void dfs2(int u){
	tot++;
	idx[u]=tot,dfn[tot]=u;
	last[top[u]]=max(last[top[u]],tot);
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
		f[u][0]+=min(f[v][0],f[v][1]+1);
		f[u][1]+=min(f[v][0]+1,f[v][1]);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		dfs2(v);
		f[u][0]+=min(f[v][0],f[v][1]+1);
		f[u][1]+=min(f[v][0]+1,f[v][0]);
		g[u][0]+=min(f[v][0],f[v][1]+1);
		g[u][1]+=min(f[v][0]+1,f[v][0]);
	}
	mat[u].a[0][0]=g[u][0],mat[u].a[0][1]=g[u][0]+1;
	mat[u].a[1][0]=g[u][1]+1,mat[u].a[1][1]=g[u][1];
}
matrix tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void build(int k,int l,int r){
	if(l==r){
		tree[k]=mat[dfn[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[k]=tree[ls]*tree[rs];
}
void modify(int k,int l,int r,int x){
	if(l==r){
		tree[k]=mat[dfn[x]];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x);
	else modify(rs,mid+1,r,x);
	tree[k]=tree[ls]*tree[rs];
}
matrix query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k];
	int mid=(l+r)>>1;
	if(y<=mid)return query(ls,l,mid,x,y);
	if(x>mid)return query(rs,mid+1,r,x,y);
	return query(ls,l,mid,x,mid)*query(rs,mid+1,r,mid+1,y);
}
int color[N];
void update(int u,int v){
	mat[u].a[0][0]=g[u][0],mat[u].a[0][1]=g[u][0]+1;
	mat[u].a[1][0]=g[u][1]+1,mat[u].a[1][1]=g[u][1];
	color[u]=v;
	if(color[u])mat[u].a[v-1][0]=mat[u].a[v-1][1]=0x3f3f3f3f;
	while(u){
		auto pre=query(1,1,n,idx[top[u]],last[top[u]]);
		modify(1,1,n,idx[u]);
		auto now=query(1,1,n,idx[top[u]],last[top[u]]);
		u=fa[top[u]];
		g[u][0]+=min(min(now.a[0][0],now.a[0][1]),min(now.a[1][0],now.a[1][1])+1)-min(min(pre.a[0][0],pre.a[0][1]),min(pre.a[1][0],pre.a[1][1])+1);
		g[u][1]+=min(min(now.a[0][0],now.a[0][1])+1,min(now.a[1][0],now.a[1][1]))-min(min(pre.a[0][0],pre.a[0][1])+1,min(pre.a[1][0],pre.a[1][1]));
		mat[u].a[0][0]=g[u][0],mat[u].a[0][1]=g[u][0]+1;
		mat[u].a[1][0]=g[u][1]+1,mat[u].a[1][1]=g[u][1];
		if(color[u])mat[u].a[color[u]-1][0]=mat[u].a[color[u]-1][1]=0x3f3f3f3f;
	}
}
void initialize(int N, std::vector<int> A, std::vector<int> B) {
	n=N;
	for(int i=0;i<n-1;i++)add(A[i],B[i]),add(B[i],A[i]);
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	build(1,1,n);
}
int cat(int v) {
	update(v,1);
	auto ans=query(1,1,n,idx[1],last[1]);
	return min(min(ans.a[0][0],ans.a[0][1]),min(ans.a[1][0],ans.a[1][1]));
}
int dog(int v) {
	update(v,2);
	auto ans=query(1,1,n,idx[1],last[1]);
	return min(min(ans.a[0][0],ans.a[0][1]),min(ans.a[1][0],ans.a[1][1]));
}
int neighbor(int v) {
	update(v,0);
	auto ans=query(1,1,n,idx[1],last[1]);
	return min(min(ans.a[0][0],ans.a[0][1]),min(ans.a[1][0],ans.a[1][1]));
}