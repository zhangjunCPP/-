#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+10,M=150+10,mod=10007;
int n,k;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp1[N][M];
void dfs1(int u,int fa){
	dp1[u][0]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs1(v,u);
		for(int j=1;j<=k;j++)dp1[u][j]=(dp1[u][j]+dp1[v][j]+dp1[v][j-1])%mod;
		dp1[u][0]=(dp1[u][0]+dp1[v][0])%mod;
	}
}
int dp2[N][M];
int tmp[M];
void dfs2(int u,int fa){
	for(int i=0;i<=k;i++)dp2[u][i]=dp1[u][i];
	if(fa){
		for(int i=1;i<=k;i++)tmp[i]=(dp2[fa][i]-dp1[u][i]+mod-dp1[u][i-1]+mod)%mod;
		tmp[0]=(dp2[fa][0]-dp1[u][0]+mod)%mod;
		for(int i=1;i<=k;i++)dp2[u][i]=(dp2[u][i]+tmp[i]+tmp[i-1])%mod;
		dp2[u][0]=(dp2[u][0]+tmp[0])%mod;
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2(v,u);
	}
}
int fac[N];
int strl[M][M];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	fac[0]=1;
	for(int i=1;i<=k;i++)fac[i]=fac[i-1]*i%mod;
	strl[0][0]=strl[1][1]=1;
	for(int i=2;i<=k;i++)
		for(int j=1;j<=i;j++)
			strl[i][j]=(strl[i-1][j-1]+j*strl[i-1][j])%mod;
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=0;j<=k;j++)ans=(ans+fac[j]*strl[k][j]%mod*dp2[i][j]%mod)%mod;
		cout<<ans<<'\n';
	}
}