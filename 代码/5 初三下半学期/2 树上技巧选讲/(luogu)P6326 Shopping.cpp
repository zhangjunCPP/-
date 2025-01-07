#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis[N];
int siz[N];
int rt;
vector<int> dfn;
void dfs(int u,int fa,int sum){
	siz[u]=1;
	int Max=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa||vis[v])continue;
		dfs(v,u,sum);
		siz[u]+=siz[v];
		Max=max(Max,siz[v]);
	}
	Max=max(Max,sum-siz[u]);
	if(Max*2<=sum)rt=u;
	dfn.push_back(u);
}
void get_root(int u){
	dfs(u,0,0);
	dfs(u,0,siz[u]);
}
void get_dfn(int u){
	dfn.clear();
	dfs(u,0,0);
}
int m;
int ans[N];
int w[N],c[N],d[N];
int tmp_w[N],tmp_c[N],tmp_d[N],tmp_siz[N];
int dp[510][4010];
int work(){
	int n=dfn.size();
	for(int i=0;i<n;i++){
		int tmp=dfn[i];
		tmp_w[i+1]=w[tmp];
		tmp_c[i+1]=c[tmp];
		tmp_d[i+1]=d[tmp];
		tmp_siz[i+1]=siz[tmp];
	}
	for(int i=1;i<=n;i++){
		memcpy(dp[i],dp[i-tmp_siz[i]],sizeof dp[i]);
		for(int j=1;j<=m;j++){
			for(int k=1;k<=min(tmp_d[i],j/tmp_c[i]);k++){
				dp[i][j]=max(dp[i][j],dp[i-1][j-k*tmp_c[i]]+k*tmp_w[i]);
			}
		}
	}
	return dp[n][m];
}
void calc(int u){
	get_root(u);
	int tmp=rt;
	get_dfn(rt);
	rt=tmp;
	ans[rt]=work();
	vis[rt]=true;
	for(int i=first[rt];i;i=a[i].nex){
		int v=a[i].v;
		if(vis[v])continue;
		calc(v);
	}
}
void init(){
	memset(first,0,sizeof first);
	memset(vis,0,sizeof vis);
	cnt=0;
}
void solve(){
	init();
	int n;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>w[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	calc(1);
	int sum=0;
	for(int i=1;i<=n;i++)sum=max(sum,ans[i]);
	cout<<sum<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}