#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int u,v,w;
}a[N];
vector<int> G[N];
int col[N];
int tot[2];
int L[N],R[N],dfn;
int belong[N];
void dfs(int u,int dad){
	belong[u]=dfn;
	for(int v:G[u]){
		if(v==dad)continue;
		dfs(v,u);
	}
}
int fa[N],siz[N],siz0[N];
void dfs2(int u){
	L[u]=dfn+1;
	siz[u]=1;
	siz0[u]=(col[u]==0);
	for(int v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dfs2(v);
		siz[u]+=siz[v];
		siz0[u]+=siz0[v];
	}
	if(siz[u]==tot[0])dfn++,dfs(u,fa[u]);
	if(siz[u]==tot[1])dfn++,dfs(fa[u],u);
	R[u]=dfn;
}
#define ls (k<<1)
#define rs (k<<1|1)
struct node2{
	int Min,lazy;
}tree[N<<2];
void update(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){
		tree[k].Min+=val;
		tree[k].lazy+=val;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(ls,l,mid,x,y,val);
	if(y>mid)update(rs,mid+1,r,x,y,val);
	tree[k].Min=min(tree[ls].Min,tree[rs].Min)+tree[k].lazy;
}
void modify(int id,int val){
	int u=a[id].u,v=a[id].v;
	if(belong[v]){
		update(1,1,dfn,belong[v],belong[v],val*(siz[u]-siz0[u]));
		if(belong[v]-1>=1)update(1,1,dfn,1,belong[v]-1,val*siz0[u]);
		if(belong[v]+1<=dfn)update(1,1,dfn,belong[v]+1,dfn,val*siz0[u]);
	}
	else{
		if(L[u]<=R[u])update(1,1,dfn,L[u],R[u],val*(tot[0]-siz0[u]));
		if(L[u]-1>=1)update(1,1,dfn,1,L[u]-1,val*siz0[u]);
		if(R[u]+1<=dfn)update(1,1,dfn,R[u]+1,dfn,val*siz0[u]);
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	string s;
	cin>>n>>q>>s;
	for(int i=1;i<=n;i++){
		col[i]=s[i-1]-'0';
		tot[col[i]]++;
	}
	if(tot[0]>tot[1]){
		for(int i=1;i<=n;i++)col[i]^=1;
		swap(tot[0],tot[1]);
	}
	for(int i=1;i<n;i++){
		cin>>a[i].u>>a[i].v>>a[i].w;
		G[a[i].u].push_back(a[i].v);
		G[a[i].v].push_back(a[i].u);
	}
	dfs2(1);
	int rt;
	for(int i=1;i<=n;i++)if(!belong[i]){rt=i;break;}
	dfn=0;
	fa[rt]=0;
	dfs2(rt);
	for(int i=1;i<n;i++)if(fa[a[i].v]==a[i].u)swap(a[i].u,a[i].v);
	for(int i=1;i<n;i++)modify(i,a[i].w);
	while(q--){
		int x,y;
		cin>>x>>y;
		modify(x,y-a[x].w);
		a[x].w=y;
		cout<<tree[1].Min<<"\n";
	}
}