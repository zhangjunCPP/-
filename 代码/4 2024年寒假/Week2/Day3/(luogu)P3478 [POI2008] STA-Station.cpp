#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n;
struct edge{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]=edge{v,first[u]};
	first[u]=cnt;
}
int siz[N];
int dep[N];
void dfs(int u,int dad){
	siz[u]=1;
	dep[u]=dep[dad]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
int dp[N];
void dfs2(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dp[v]=dp[u]+n-2*siz[v];
		dfs2(v,u);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)dp[1]+=dep[i];
	dfs2(1,0);
	int id=1,Max=dp[1];
	for(int i=2;i<=n;i++){
		if(dp[i]>Max){
			id=i;
			Max=dp[i];
		}
	}
	cout<<id;
}