#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
struct node2{
	int val,id;
}tmp[N];
bool cmp1(const node2&x,const node2&y){return x.val<y.val;}
int h[N];
struct node3{
	int u,v,w;
}G[N];
bool cmp2(const node3&x,const node3&y){return x.w<y.w;}
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int val[N];
int n,m,q;
void init(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>tmp[i].val,tmp[i].id=i;
	sort(tmp+1,tmp+n+1,cmp1);
	for(int i=1;i<=n;i++)h[tmp[i].id]=i;
	for(int i=1;i<=m;i++)cin>>G[i].u>>G[i].v>>G[i].w;
	for(int i=1;i<(n<<1);i++)fa[i]=i;
}
int tot;
void Kruskal(){
	val[0]=LLONG_MAX;
	sort(G+1,G+m+1,cmp2);
	tot=n;
	for(int i=1;i<=m;i++){
		int fu=find(G[i].u),fv=find(G[i].v);
		if(fu!=fv){
			val[++tot]=G[i].w;
			add(tot,fu),add(tot,fv);
			fa[fu]=fa[fv]=tot;
			if(tot==(n<<1)-1)break;
		}
	}
}
struct node4{
	int l,r,sum;
}tree[N];
int sum;
void build(int &k,int l,int r){
	k=++sum;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(tree[k].l,l,mid);
	build(tree[k].r,mid+1,r);
}
void update(int pre,int &k,int l,int r,int x){
	k=++sum;
	tree[k]=tree[pre];
	tree[k].sum++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[pre].l,tree[k].l,l,mid,x);
	else update(tree[pre].r,tree[k].r,mid+1,r,x);
}
int query(int l,int r,int x,int y,int k){
	if(l==r){
		if(k==tree[x].sum-tree[y].sum)return l;
		else return 0;
	}
	int d=tree[tree[x].r].sum-tree[tree[y].r].sum;
	int mid=(l+r)>>1;
	if(k>d)return query(l,mid,tree[x].l,tree[y].l,k-d);
	else return query(mid+1,r,tree[x].r,tree[y].r,k);
}

int dfn,l[N],r[N];
int b[N];
int fa2[N][20];
void dfs(int u,int dad){
	fa2[u][0]=dad;
	for(int i=1;i<=19;i++)fa2[u][i]=fa2[fa2[u][i-1]][i-1];
	l[u]=dfn;
	if(first[u]==0){
		r[u]=++dfn;
		b[dfn]=u;
		return;
	}
	for(int i=first[u];i;i=a[i].nex)dfs(a[i].v,u);
	r[u]=dfn;
}
int root[N];
int calc(int u,int x){
	for(int i=19;i>=0;i--){
		if(val[fa2[u][i]]<=x)u=fa2[u][i];
	}
	return u;
}
void solve(){
	dfs(tot,0);
	build(root[0],1,n);
	for(int i=1;i<=dfn;i++)update(root[i-1],root[i],1,n,h[b[i]]);
	int last=0;
	tmp[0].val=-1;
	while(q--){
		int u,x,k;
		cin>>u>>x>>k;
		u=(u^last)%n+1;
		k=(k^last)%n+1;
		x=x^last;
		int now=calc(u,x);
		int ans= query(1,n,root[r[now]],root[l[now]],k);
		cout<<tmp[ans].val<<"\n";
		if(tmp[ans].val==-1) last=0;
		else last=tmp[ans].val;
	}
}
signed main(){
	init();
	Kruskal();
	solve();
}