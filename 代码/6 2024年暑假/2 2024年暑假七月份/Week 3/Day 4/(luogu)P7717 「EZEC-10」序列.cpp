#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e7+10;
const int mod=1e9+7;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int tree[N][2],tot=1;
void insert(int x) {
	int now=1;
	for(int i=29;i>=0;i--) {
		int tmp=(x>>i)&1;
		if(!tree[now][tmp])tree[now][tmp]=++tot;
		now=tree[now][tmp];
	}
}
void clear() {
	for(int i=1;i<=tot;i++)tree[i][0]=tree[i][1]=0;
	tot=1;
}
bool vis[N];
int dis[N];
void dfs(int u,int val) {
	vis[u]=true;
	dis[u]=val;
	insert(val);
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(!vis[v])dfs(v,val^a[i].w);
		else if((val^a[i].w)!=dis[v]){puts("0");exit(0);}
	}
}
int query(int u,int val,int dep,int k) {
	if(val>k)return 0;
	if(dep==-1)return 1;
	if(tree[u][0]&&tree[u][1])return (query(tree[u][0],val+(1<<dep),dep-1,k)+query(tree[u][1],val+(1<<dep),dep-1,k))%mod;
	int tmp=!tree[u][0];
	if(val+(1<<dep)>k)return query(tree[u][tmp],val,dep-1,k)%mod;
	return ((1<<dep)+query(tree[u][tmp],val+(1<<dep),dep-1,k))%mod;
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	int ans=1;
	for(int i=1;i<=n;i++) {
		if(!vis[i]) {
			clear();
			dfs(i,0);
			ans=ans*query(1,0,29,k)%mod;
		}
	}
	cout<<ans;
}