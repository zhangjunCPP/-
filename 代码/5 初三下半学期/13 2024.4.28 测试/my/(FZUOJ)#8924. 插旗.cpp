#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int ans;
int dp[N];
int dep[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	int mx1=0,mx2=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		int tmp=dp[v]-dep[u];
		if(tmp>mx1)mx2=mx1,mx1=tmp;
		else if(tmp>mx2)mx2=tmp;
		dp[u]=min(dp[u],dp[v]);
	}
	if(u!=1)ans=max(ans,mx1+1);
	else ans=max(ans,max(mx1,mx2+1));
	if(dp[u]==0x3f3f3f3f)dp[u]=dep[u];
}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)first[i]=0,dp[i]=0x3f3f3f3f,dep[i]=0;
	cnt=0;
	ans=2;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<ans<<"\n";
}
int main(){
	freopen("flag.in","r",stdin);
	freopen("flag.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}