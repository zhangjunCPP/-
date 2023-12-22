#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
const int mod=1e9+7;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
int n,k;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp1[N][N*5][6],dp2[N*5][6];
int siz[N];
void dfs(int u,int fa) {
	siz[u]=1;
	for(int i=1;i<=k;i++) dp1[u][0][i]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		dfs(v,u);
		memset(dp2,0,sizeof dp2);
		for(int i=0;i<=k*siz[u];i++){
			for(int j=0;j<=k;j++){
				if(dp1[u][i][j]){
					for(int l=0;l<=k*siz[v];l++){
						for(int m=0;m<=k;m++)if(dp1[v][l][m])dp2[i+l+m][max(i+j+l,i+l+m)-(i+l+m)]=(dp2[i+l+m][max(i+j+l,i+l+m)-(i+l+m)]+dp1[u][i][j]*dp1[v][l][m]%mod)%mod;
					}
				}
			}
		}
		memcpy(dp1[u],dp2,sizeof dp2);
		siz[u]+=siz[v];
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n*k;i++) {
		int ans=0;
		for(int j=0;j<=min(i,k);j++) ans=(ans+dp1[1][i-j][j])%mod;
		cout<<ans<<"\n";
	}
}
