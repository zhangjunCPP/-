#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N];
int n;
int a[N];
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int siz[N],edge[N];
int sz[N],tot;
int dp[N][N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]==-1)cnt++;
		else{
			int fx=find(i),fy=find(a[i]);
			if(fx==fy)edge[fx]++;
			else{
				fa[fy]=fx;
				siz[fx]+=siz[fy],edge[fx]+=edge[fy]+1;
				siz[fy]=edge[fy]=0;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			if(siz[i]==edge[i])ans=(ans+qpow(n,cnt)%mod)%mod;
			else sz[++tot]=siz[i];
		}
	}
	dp[0][0]=1;
	for(int i=1;i<=tot;i++){
		dp[i][0]=1;
		for(int j=1;j<=i;j++)dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]*sz[i]%mod)%mod;
	}
	for(int i=1;i<=tot;i++)ans=(ans+dp[tot][i]*fac[i-1]%mod*qpow(n,cnt-i)%mod)%mod;
	cout<<ans;
}