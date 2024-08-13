#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=1e9+7;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
struct node {
	int v,nex;
}a[N];
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
int sum_e[N];
int siz[N];
void dfs(int u,int fa) {
	siz[u]=sum_e[u];
	for(int v:G[u]) {
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v]+1;
	}
}
int dp[N][2];
int ans;
void solve(int u,int fa) {
	for(int v:G[u]) {
		if(v==fa)continue;
		solve(v,u);
		dp[u][1]=(dp[u][1]*((dp[v][0]*2+dp[v][1])%mod)%mod+dp[u][0]*dp[v][1]%mod)%mod;
		dp[u][0]=dp[u][0]*dp[v][0]%mod*2%mod;
	}
	if(u==1)ans=(ans+dp[u][1])%mod;
	else ans=(ans+dp[u][1]*qpow(2,siz[1]-siz[u]-1)%mod)%mod;
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	Tarjan(1,0);
	for(int u=1;u<=n;u++) {
		for(int i=first[u];i;i=a[i].nex) {
			int v=a[i].v;
			if(belong[u]!=belong[v])G[belong[u]].push_back(belong[v]);
			else sum_e[belong[u]]++;
		}
	}
	for(int i=1;i<=scc;i++)sum_e[i]/=2;
	dfs(1,0);
	for(int i=1;i<=scc;i++) {
		dp[i][0]=qpow(2,sum_e[i]);
		dp[i][1]=qpow(2,sum_v[i]+sum_e[i])-qpow(2,sum_e[i]);
	}
	solve(1,0);
	cout<<ans;
}