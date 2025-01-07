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
int n,k;
int dep[N];
int pre[N];

int last;
void dfs(int u,int fa,int tmp){
	dep[u]=dep[fa]+1;
	if(tmp==2) pre[u]=fa;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		dfs(v,u,tmp);
	}
	if(dep[u]>dep[last]) last=u;
}
bool vis[N];
int ans2;
int d[N];
void dp(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		if(vis[u]&&vis[v]) a[i].w=-1;
		dp(v,u);
		ans2=max(ans2,d[u]+d[v]+a[i].w);
		d[u]=max(d[u],d[v]+a[i].w);
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v,1);
		add(v,u,1);
	}
	dep[0]=-1;
	dfs(1,0,1);
	dfs(last,0,2);
	int ans1=dep[last];
	if(k==1) {
		cout<<2*(n-1)-ans1+1;
		return 0;
	}
	for(int i=last;i;i=pre[i])vis[i]=true;
	dp(1,0);
	cout<<2*n-ans1-ans2;
	return 0;
}
