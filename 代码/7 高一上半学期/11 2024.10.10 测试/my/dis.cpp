#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int n,m;	
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int ans[N];
int dp[N];
void dfs1(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs1(v,u);
		dp[u]=max(dp[u],dp[v]);
	}
	dp[u]++;
}
void dfs2(int u,int fa,int val){
	int Max1=val,Max2=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		if(dp[v]>Max1)Max2=Max1,Max1=dp[v];
		else if(dp[v]>Max2)Max2=dp[v];
	}
	ans[u]=max(ans[u],Max1+Max2);
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2(v,u,(dp[v]==Max1?Max2:Max1)+1);
	}
}
void solve1(){
	dfs1(1,0);dfs2(1,0,0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return;
}
void solve2(){
	solve1();
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	if(m==n-1)solve1();
	else solve2();
	return 0;
}