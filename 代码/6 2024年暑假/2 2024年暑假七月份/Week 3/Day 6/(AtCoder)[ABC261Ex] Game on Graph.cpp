#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int INF=1e18;
int n,m,s;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int deg[N];
struct node2 {
	int id,opt,val;
	bool operator<(const node2&oth)const {return val>oth.val;}
};
int dp[N][2];
bool vis[N][2];
void dij() {
	priority_queue<node2>q;
	for(int i=1;i<=n;i++) {
		if(!deg[i]) {
			dp[i][0]=dp[i][1]=0;
			q.push({i,0,0});
			q.push({i,1,0});
		}
		else dp[i][0]=INF,dp[i][1]=-INF;
	}
	while(!q.empty()) {
		auto now=q.top();
		q.pop();
		int u=now.id,opt=now.opt;
		if(vis[u][opt])continue;
		vis[u][opt]=true;
		if(opt==0) {
			for(int i=first[u];i;i=a[i].nex) {
				int v=a[i].v;
				deg[v]--;
				if(dp[v][1]<dp[u][0]+a[i].w)dp[v][1]=dp[u][0]+a[i].w;
				if(!deg[v])q.push({v,1,dp[v][1]});
			}
		}
		else {
			for(int i=first[u];i;i=a[i].nex) {
				int v=a[i].v;
				if(dp[v][0]>dp[u][1]+a[i].w) {
					dp[v][0]=dp[u][1]+a[i].w;
					q.push({v,0,dp[v][0]});
				}
			}
		}
	}
}
signed main() {
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		deg[u]++;
		add(v,u,w);
	}
	dij();
	if(!vis[s][0])puts("INFINITY");
	else cout<<dp[s][0];
}