#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e6+10;
const int mod=998244353;
int w[N];
vector<int> G[N];
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis[N];
int dp[N];
void dfs(int u,int fa){
	dp[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa||vis[v])continue;
		dfs(v,u);
		dp[u]=dp[u]*(dp[v]+1)%mod;
	}
}
int ans[N];
signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
		G[w[i]].push_back(i);
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	for(int i=m;i>=1;i--){
		for(int u:G[i]){
			if(vis[u])continue;
			dfs(u,0);
			vis[u]=true;
			ans[i]=(ans[i]+dp[u])%mod;
		}
	}
	for(int i=1;i<=m;i++)cout<<ans[i]%mod<<" ";
}