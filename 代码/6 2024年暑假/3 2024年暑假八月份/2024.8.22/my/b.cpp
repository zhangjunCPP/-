#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node {
	int v,nex;
}a[N*10];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dfn[N],low[N],tot;
bool vis[N];
stack<int>s;
int scc;
int sum_v[N];
int belong[N];
void Tarjan(int u,int fa) {
	dfn[u]=low[u]=++tot;
	s.push(u);
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==fa)continue;
		if(!dfn[v])Tarjan(v,u),low[u]=min(low[u],low[v]);
		else if(vis[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		scc++;
		while(s.top()!=u) {
			sum_v[scc]++;
			belong[s.top()]=scc;
			vis[s.top()]=false;
			s.pop();
		}
		sum_v[scc]++;
		belong[s.top()]=scc;
		vis[s.top()]=false;
		s.pop();
	}
}
vector<int>G[N];
bool vis2[N];
bitset<N>f,g;
int dfs1(int u) {
	vis2[u]=true;
	int siz=sum_v[u];
	for(int v:G[u])if(!vis2[v])siz+=dfs1(v);
	return siz;
}
int dfs2(int u,int sum) {
	vis2[u]=true;
	int siz=sum_v[u];
	for(int v:G[u])if(!vis2[v])siz+=dfs2(v,sum);
	f|=g>>siz;
	f|=g>>(sum-siz);
	// cout<<"u="<<u<<" siz="<<siz<<"\n";
	return siz;
}
int sum[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int n,m,c;
	cin>>n>>m>>c;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	if(scc==1){puts("-1");return 0;}
	for(int i=1;i<=n;i++) {
		for(int j=first[i];j;j=a[j].nex) {
			int v=a[j].v;
			if(belong[i]!=belong[v])G[belong[i]].push_back(belong[v]);
		}
	}
	// cout<<scc<<"\n";
	// for(int i=1;i<=n;i++)cout<<G[i].size()<<" ";
	// cout<<"\n";
	f[0]=1;
	int ans=0;
	for(int i=1;i<=scc;i++) {
		if(!vis2[i]) {
			ans+=c;
			sum[i]=dfs1(i);
			f|=f<<sum[i];
		}
	}
	ans-=c;
	memset(vis2,false,sizeof vis2);
	g=f;
	for(int i=1;i<=scc;i++)if(!vis2[i])dfs2(i,sum[i]);

	int x=n/2;
	while(!f[x])x--;
	cout<<ans+x*x+(n-x)*(n-x);
	return 0;
}
/*
6 6 2
1 4
2 5
3 6
1 5
3 5
6 5
*/
