#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n;
int val[N];
struct node{
	int v,nex;
}a[N<<1];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
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
int f[N];
int dep[N],siz[N],fa[N],son[N];
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
int top[N];
int idx[N],dfn[N],last[N],tot;
void dfs2(int u){
	tot++;
	idx[u]=tot,dfn[tot]=u;
	last[top[u]]=max(last[top[u]],tot);
	mat[u].a[0][1]=val[u];
	mat[u].a[1][1]=mat[u].a[0][0]=0;
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
		f[u]+=f[v];
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		dfs2(v);
		mat[u].a[0][0]+=f[v];
		f[u]+=f[v];
	}
	if(!son[u])f[u]=val[u];
	else f[u]=min(f[u],val[u]);
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
void update(int u,int v){
	val[u]+=v;
	mat[u].a[0][1]+=v;
	while(u){
		auto pre=query(1,1,n,idx[top[u]],last[top[u]]);
		modify(1,1,n,idx[u]);
		auto now=query(1,1,n,idx[top[u]],last[top[u]]);
		u=fa[top[u]];
		mat[u].a[0][0]+=now.a[0][1]-pre.a[0][1];
	}
}
int query(int x){
	auto ans=query(1,1,n,idx[x],last[top[x]]);
	return ans.a[0][1];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	build(1,1,n);
	int m;
	cin>>m;
	while(m--){
		string opt;
		cin>>opt;
		if(opt=="Q"){
			int x;
			cin>>x;
			cout<<query(x)<<"\n";
		}
		else{
			int x,t;
			cin>>x>>t;
			update(x,t);
		}
	}
}