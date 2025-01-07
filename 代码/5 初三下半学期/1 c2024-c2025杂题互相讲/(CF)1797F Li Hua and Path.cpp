#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n;
struct node{int v,nex;}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
struct node2{int x,y;}G[N];
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int siz1[N],siz2[N];
bool cmp1(const node2&x,const node2&y){return x.y<y.y;}
bool cmp2(const node2&x,const node2&y){return x.x>y.x;}
int dfn[N],tot;
void dfs(int u){
	dfn[u]=++tot;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v);
	}
}
int tree[N];
int lowbit(int x){return x&(-x);}
void update(int x,int y){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=y;}
int query(int x){int ans=0;for(int i=x;i;i-=lowbit(i))ans+=tree[i];return ans;}
int ans;
void dfs2(int u){
	ans-=(query(dfn[u]+siz1[u]-1)-query(dfn[u]-1))*2;
	update(dfn[u],1);
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs2(v);
	}
	update(dfn[u],-1);
}
int dep[N];
int dad[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)fa[i]=i,siz1[i]=siz2[i]=1;
	for(int i=1;i<n;i++){
		cin>>G[i].x>>G[i].y;
		if(G[i].x>G[i].y)swap(G[i].x,G[i].y);
	}
	sort(G+1,G+n,cmp1);
	for(int i=1;i<n;i++){
		int x=find(G[i].x),y=G[i].y;
		fa[x]=y;
		siz1[y]+=siz1[x];
		add(y,x);
	}
	for(int i=1;i<=n;i++)ans+=siz1[i];
	dfs(n);
	for(int i=1;i<=n;i++)fa[i]=i,first[i]=0;
	cnt=tot=0;
	sort(G+1,G+n,cmp2);
	for(int i=1;i<n;i++){
		int x=G[i].x,y=find(G[i].y);
		fa[y]=x;
		dad[y]=x;
		siz2[x]+=siz2[y];
		add(x,y);
	}
	dfs2(1);
	dep[0]=1;
	for(int i=1;i<=n;i++){
		ans+=siz2[i];
		dep[i]=dep[dad[i]]+1;
	}
	ans-=n*2;
	cout<<ans<<"\n";

	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		dep[i+n]=dep[x]+1;
		ans+=(i+n)-dep[x];
		cout<<ans<<"\n";
	}
}