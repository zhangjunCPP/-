#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
const int mod=1e9+7;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int dp[N][N][2];
int tmp[N][2];
int siz[N];
void dfs(int u,int fa) {
	dp[u][1][0]=dp[u][1][1]=1;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		memset(tmp,0,sizeof tmp);
		for(int j=1;j<=siz[u];j++) {
			for(int k=1;k<=siz[v];k++) {
				tmp[j+k][0]=(tmp[j+k][0]+dp[u][j][0]*dp[v][k][1]%mod)%mod;
				tmp[j+k][1]=(tmp[j+k][1]+dp[u][j][1]*dp[v][k][1]%mod)%mod;
				tmp[j+k-1][0]=(tmp[j+k-1][0]+dp[u][j][0]*dp[v][k][0]%mod)%mod;
				tmp[j+k-1][1]=(tmp[j+k-1][1]+dp[u][j][1]*dp[v][k][0]%mod+dp[u][j][0]*dp[v][k][1]%mod)%mod;
			}
		}
		siz[u]+=siz[v];
		for(int j=1;j<=siz[u];j++)for(int k=0;k<=1;k++)dp[u][j][k]=tmp[j][k];
	}
}
int C[N][N];
int Pow[N];
void init(int n) {
	for(int i=0;i<=n;i++) {
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	Pow[0]=1;
	for(int i=1;i<=n;i++)Pow[i]=Pow[i-1]*n%mod;
}
int f[N];
int g[N];
signed main() {
	int n;
	cin>>n;
	init(n);
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=0;i<=n-2;i++)g[i]=dp[1][n-i][1]%mod*Pow[n-i-2]%mod;
	g[n-1]=1;
	for(int i=0;i<=n-1;i++)for(int j=i;j<=n-1;j++)f[i]=(f[i]+((j-i)&1?-1:1)*C[j][i]%mod*g[j]%mod+mod)%mod;
	for(int i=0;i<=n-1;i++)cout<<f[i]<<" ";
}