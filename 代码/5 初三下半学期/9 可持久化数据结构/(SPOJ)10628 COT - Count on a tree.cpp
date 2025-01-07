#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,q;
int t[N];
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt].v=v;
	a[cnt].nex=first[u];
	first[u]=cnt;
}
struct node2{
	int ls,rs,val;
}tree[N*100];
int tot;
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void update(int &k1,int k2,int l,int r,int x,int val){
	k1=clone(k2);
	tree[k1].val+=val;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k1].ls,tree[k2].ls,l,mid,x,val);
	else update(tree[k1].rs,tree[k2].rs,mid+1,r,x,val);
}
int rt[N];
int num[2];
int need[2][N];
void ask(int x,int opt){need[opt][++num[opt]]=rt[x];}
int query(int l,int r,int k){
	if(l==r)return l;
	int sum=0;
	for(int i=1;i<=num[1];i++)sum+=tree[tree[need[1][i]].ls].val;
	for(int i=1;i<=num[0];i++)sum-=tree[tree[need[0][i]].ls].val;
	int mid=(l+r)>>1;
	if(k<=sum){
		for(int i=1;i<=num[1];i++)need[1][i]=tree[need[1][i]].ls;
		for(int i=1;i<=num[0];i++)need[0][i]=tree[need[0][i]].ls;
		return query(l,mid,k);
	}
	else {
		for(int i=1;i<=num[1];i++)need[1][i]=tree[need[1][i]].rs;
		for(int i=1;i<=num[0];i++)need[0][i]=tree[need[0][i]].rs;
		return query(mid+1,r,k-sum);
	}
}
int siz[N],fa[N],dep[N],son[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	dep[u]=dep[dad]+1;
	siz[u]=1;
	update(rt[u],rt[dad],1,n,t[u],1);
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N];
void dfs2(int u){
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
int lca(int x,int y){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int tmp[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>t[i],tmp[i]=t[i];
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++)t[i]=lower_bound(tmp+1,tmp+n+1,t[i])-tmp;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	int lastans=0;
	while(q--){
		int x,y,k;
		cin>>x>>y>>k;
		int LCA=lca(x,y);
		num[0]=num[1]=0;
		ask(x,1);ask(y,1);ask(LCA,0);ask(fa[LCA],0);
		cout<<(lastans=tmp[query(1,n,k)])<<"\n";
	}
}