#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
vector<int>G[N];
int fa[N];
void dfs(int u,int dad) {
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
	}
}
int ans[N];
bool vis[N];
int dp[N];
void solve(int u,int w) {
	ans[w]=(ans[w]-dp[u]+mod)%mod;
	dp[u]=1;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(fa[u]==v)continue;
		dp[u]=dp[u]*(1+dp[v])%mod;
	}
	ans[w]=(ans[w]+dp[u])%mod;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		int w;
		cin>>w;
		G[w].push_back(i);
	}
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++) {
		ans[i]=ans[i-1];
		for(int u:G[i]) {
			vis[u]=true;
			while(u&&vis[u]){solve(u,i),u=fa[u];}
		}
	}
	for(int i=1;i<=m;i++)cout<<(ans[i]-ans[i-1]+mod)%mod<<" ";
}