#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,k;
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
int ans;
void dfs(int u,int fa){
	siz[u]=1;
	int tot=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		tot+=siz[v]>=k;
	}
	dp[u]=tot;
	int Max1=-1,Max2=-1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		int tmp=dp[v]-(siz[v]>=k);
		dp[u]=max(dp[u],tmp+tot);
		if(tmp>Max1)Max2=Max1,Max1=tmp;
		else if(tmp>Max2)Max2=tmp;
	}
	tot+=(n-siz[u])>=k;
	ans=max({ans,tot+Max1,tot+Max1+Max2});
}
void solve(){
	memset(first,0,sizeof first);
	cnt=0;
	ans=0;
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs(1,0);
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}