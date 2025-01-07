#include <bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=5e6+10;
const int INF=1e6;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N],fa[N],siz[N],son[N];
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
int id[N],tot;
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
	int lmx[2]={0,0},rmx[2]={0,0},dis[2][2]={0,0,0,0};
	node2 operator+(const node2&oth){
		node2 ans;
		ans.lmx[0]=max({lmx[0],dis[0][0]+oth.lmx[0],dis[0][1]+oth.lmx[1]});
		ans.lmx[1]=max({lmx[1],dis[1][0]+oth.lmx[0],dis[1][1]+oth.lmx[1]});
		ans.rmx[0]=max({oth.rmx[0],oth.dis[0][0]+rmx[0],oth.dis[1][0]+rmx[1]});
		ans.rmx[1]=max({oth.rmx[1],oth.dis[0][1]+rmx[0],oth.dis[1][1]+rmx[1]});
		ans.dis[0][0]=max(dis[0][0]+oth.dis[0][0],dis[0][1]+oth.dis[1][0]);
		ans.dis[0][1]=max(dis[0][0]+oth.dis[0][1],dis[0][1]+oth.dis[1][1]);
		ans.dis[1][0]=max(dis[1][0]+oth.dis[0][0],dis[1][1]+oth.dis[1][0]);
		ans.dis[1][1]=max(dis[1][0]+oth.dis[0][1],dis[1][1]+oth.dis[1][1]);
		return ans;
	}
}tree[N*4];
void update(int k,int x,int y){
	tree[k].lmx[0]=tree[k].rmx[0]=x;
	tree[k].lmx[1]=tree[k].rmx[1]=y;
	tree[k].dis[0][0]=x?x:-INF;
	tree[k].dis[1][1]=y?y:-INF;
	tree[k].dis[0][1]=tree[k].dis[1][0]=x&&y?2:-INF;
}
void change(int k,int l,int r,int x,int v1,int v2){
	if(l==r){
		update(k,v1,v2);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change(ls,l,mid,x,v1,v2);
	else change(rs,mid+1,r,x,v1,v2);
	tree[k]=tree[ls]+tree[rs];
}
node2 query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k];
	int mid=(l+r)>>1;
	if(x>mid)return query(rs,mid+1,r,x,y);
	if(y<=mid)return query(ls,l,mid,x,y);
	return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
int n,m;
int ask(int x,int y){
	node2 ans1,ans2;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]>dep[fy]){
			ans1=query(1,1,n,id[fx],id[x])+ans1;
			x=fa[fx];
			fx=top[x];
		}
		else{
			ans2= query(1,1,n,id[fy],id[y])+ans2;
			y=fa[fy];
			fy=top[y];
		}
	}
	if(dep[x]>dep[y]) ans1=query(1,1,n,id[y],id[x])+ans1;
	else ans2=query(1,1,n,id[x],id[y])+ans2;
	swap(ans1.lmx[0],ans1.rmx[0]);
	swap(ans1.lmx[1],ans1.rmx[1]);
	swap(ans1.dis[0][1],ans1.dis[1][0]);
	node2 ans=ans1+ans2;
	return max(ans.lmx[0],ans.lmx[1]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
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
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		change(1,1,n,id[i],s[0]=='.',s[1]=='.');
	}
	while(m--){
		string s;
		cin>>s;
		if(s=="C"){
			int u;
			cin>>u>>s;
			change(1,1,n,id[u],s[0]=='.',s[1]=='.');
		}
		else {
			int u,v;
			cin>>u>>v;
			cout<<ask(u,v)<<"\n";
		}
	}
}