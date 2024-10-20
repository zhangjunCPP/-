#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int INF=1e18;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int ans[N];
bool vis[N];
void dfs(int u,int Min,int Max){
	ans[u]=min(ans[u],Min+Max);
	for(int i=first[u];i;i=a[i].nex){
		if(vis[i])continue;
		vis[i]=vis[i^1]=true;
		int v=a[i].v;
		dfs(v,min(Min,a[i].w),max(Max,a[i].w));
		vis[i]=vis[i^1]=false;
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=2;i<=n;i++)ans[i]=INF;
	dfs(1,INF,0);
	for(int i=2;i<=n;i++)cout<<ans[i]<<"\n";
}