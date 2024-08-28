#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
const int mod=1e9+7;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int w[N];
struct node2 {
	double val;
	int x;
	node2 operator+(const node2&oth)const {
		return {val+oth.val,x*oth.x%mod};
	}
}dp[N][2];
node2 Max(node2 u,node2 v) {
	node2 ans=u.val>v.val?u:v;
	return ans;
}
void dfs(int u,int fa) {
	dp[u][0]={0,1};
	dp[u][1]={log(w[u]),w[u]};
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		dp[u][0]=dp[u][0]+Max(dp[v][0],dp[v][1]);
		dp[u][1]=dp[u][1]+dp[v][0];
	}
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>w[i];
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<Max(dp[1][0],dp[1][1]).x;
}