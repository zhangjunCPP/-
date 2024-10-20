#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e6+10;
const int INF=1e9;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N];
int dp[N];
int dp2[N];
void dfs(int u,int fa){
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa){
	int sum=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2(v,u);
		dp[u]+=dp[v];
		dp[u]+=dp2[v];
		dp2[u]+=siz[v]*sum;
		sum+=siz[v];
	}
}
int dp3[N];
void dfs3(int u,int fa,int Siz){
	// cout<<u<<" "<<Siz<<" "<<val1<<" "<<val2<<"\n";
	// dp3[u]=val1+val2;
	int tmp_Siz=Siz-(siz[fa]-siz[u]);
	if(u!=1)dp3[u]=(dp2[fa]-siz[u]*(siz[fa]-siz[u]-1)+tmp_Siz*(siz[fa]-siz[u]-1))+(dp[fa]-dp[u]-dp2[u]+dp3[fa]);
	for(int i=first[u];i;i=a[i].nex){//换根
		int v=a[i].v;
		if(v==fa)continue;
		dfs3(v,u,Siz+(siz[u]-siz[v]));
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("fruit.in","r",stdin);
	freopen("fruit.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v);add(v,u);
	}
	dfs(1,0);
	dfs2(1,0);
	// for(int i=1;i<=n;i++)cout<<"i="<<i<<" "<<dp[i]<<" "<<dp2[i]<<"\n";
	dfs3(1,0,0);
	int sum=0;
	for(int i=1;i<=n;i++)/*cout<<dp[i]<<" "<<dp3[i]<<"\n",*/sum+=dp[i]+dp3[i];
	cout<<sum/3;
	// cout<<"\n";
}
/*
三者肯定不在同一条线上
小小T1,直接拿下
*/