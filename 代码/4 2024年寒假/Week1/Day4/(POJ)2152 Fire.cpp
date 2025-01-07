#include <cstring>
#include <iostream>
using namespace std;
const int N=1010;

int n,W[N],D[N];
struct node{
	int v,w,nex;
}a[N<<1];
int cnt,first[N];
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}

int root,dis[N][N];
void getdis(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v,w=a[i].w;
		if(v==fa)continue;
		dis[root][v]=dis[root][u]+w;
		getdis(v,u);
	}
}

int dp1[N],dp2[N][N];
void dfs(int u,int fa){
	dp1[u]=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		if(dis[u][i]<=D[u])dp2[u][i]=W[i];
		else dp2[u][i]=0x3f3f3f3f;
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		for(int j=1;j<=n;j++)if(dis[u][j]<=D[u])dp2[u][j]+=min(dp2[v][j]-W[j],dp1[v]);
	}
	for(int i=1;i<=n;i++)dp1[u]=min(dp1[u],dp2[u][i]);
}

void init(){
	memset(first,0,sizeof first);
	cnt=0;
}
void solve(){
	init();
	cin>>n;
	for(int i=1;i<=n;i++)cin>>W[i];
	for(int i=1;i<=n;i++)cin>>D[i];
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=n;i++)root=i,getdis(root,0);
	dfs(1,0);
	cout<<dp1[1]<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
} 