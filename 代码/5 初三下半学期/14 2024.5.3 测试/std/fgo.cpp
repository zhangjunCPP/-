#include<bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=1005,MOD=998244353;
int n,a[N][4],sz[N],ans;
int power(int x,int y){
	int ans=1;
	for(;y;y>>=1,x=1ll*x*x%MOD) if(y&1) ans=1ll*ans*x%MOD;
	return ans;
}
void add(int &x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; }
int ad(int x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; return x; }
int dp[N][N*3],tmp[N*3];
vector<pii> edge[N];
void dfs(int x,int fa){
	dp[x][0]=1;
	for(auto [y,v]:edge[x]) if(y^fa){
		dfs(y,x);
		for(int i=0;i<=sz[x];++i) tmp[i]=dp[x][i],dp[x][i]=0;
		if(v) for(int i=0;i<=sz[x];++i) for(int j=0;j<=sz[y];++j) add(dp[x][i+j],1ll*tmp[i]*dp[y][j]%MOD);
		else for(int i=0;i<=sz[x];++i) for(int j=0;j<=sz[y];++j) add(dp[x][i+j],-1ll*tmp[i]*dp[y][j]%MOD),add(dp[x][i],1ll*tmp[i]*dp[y][j]%MOD);
		sz[x]+=sz[y];
	}
	sz[x]+=3;
	for(int i=sz[x];~i;--i){
		dp[x][i]=0;
		for(int j=1;j<=min(3,i);++j) add(dp[x][i],1ll*dp[x][i-j]*a[x][j]%MOD*j%MOD*power(i,MOD-2)%MOD);
	}
}
int main(){
	freopen("fgo.in","r",stdin);
	freopen("fgo.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=3;++j) scanf("%d",&a[i][j]);
		int t=power(ad(a[i][1],ad(a[i][2],a[i][3])),MOD-2);
		for(int j=1;j<=3;++j) a[i][j]=1ll*t*a[i][j]%MOD;
	}
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),edge[u].pb({v,1}),edge[v].pb({u,0});
	dfs(1,0);
	for(int i=0;i<=sz[1];++i) add(ans,dp[1][i]);
	printf("%d\n",ans);
	return 0;
}
