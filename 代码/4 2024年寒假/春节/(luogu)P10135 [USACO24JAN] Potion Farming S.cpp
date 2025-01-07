#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp[N];
int p[N];
int num[N];
int tot;
int ans;
void dfs(int u,int fa){
	int tmp=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		tmp++;
		dfs(v,u);
	}
	if(tmp==0){tot++;dp[u]=1;}
}
void dfs2(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2(v,u);
	}
	ans+=min(num[u],dp[u]);
	dp[u]-=min(num[u],dp[u]);
	dp[fa]+=dp[u];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=tot;i++)num[p[i]]++;
	dfs2(1,0);
	cout<<ans;
	return 0;
}