#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int dep[N];
int fa[N];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
	}
}
bool vis[N];
int ans2;
int f[N];
void dp(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		if(vis[u]&&vis[v]) a[i].w=-1;
		dp(v,u);
		ans2=max(ans2,f[u]+f[v]+a[i].w);
		f[u]=max(f[u],f[v]+a[i].w);
	}
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v,1);
		add(v,u,1);
	}
	dep[0]=-1;
	dfs(1,0);
	int rt1=1;
	for(int i=1;i<=n;i++)if(dep[i]>dep[rt1])rt1=i;
	dfs(rt1,0);
	int rt2=1;
	for(int i=1;i<=n;i++)if(dep[i]>dep[rt2])rt2=i;
	int ans1=dep[rt2];
	if(k==1){
		cout<<2*(n-1)-ans1+1;
		return 0;
	}
	for(int i=rt2;i;i=fa[i])vis[i]=true;
	dp(1,0);
	cout<<2*n-ans1-ans2;
	return 0;
}