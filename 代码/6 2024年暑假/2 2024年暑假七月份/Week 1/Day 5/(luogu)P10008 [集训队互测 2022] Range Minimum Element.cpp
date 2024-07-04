#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10,M=1e5+10;
const int mod=998244353;
int l[M],r[M];
int v[N][N];
int diff[M];
int dp[N][N][N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int val[N];
signed main(){
	int n,m,c;
	cin>>n>>m>>c;
	for(int i=1;i<=m;i++)cin>>l[i]>>r[i];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=1;k<=n;k++)diff[k]=0;
			for(int k=1;k<=m;k++)if(l[k]>=i&&r[k]<=j)diff[l[k]]++,diff[r[k]+1]--;
			for(int k=1;k<=n;k++)diff[k]+=diff[k-1];
			v[i][j]=1;
			for(int k=i;k<=j;k++)if(!diff[k]){v[i][j]=0;break;}
		}
	}
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)dp[i][j][n+1]=1;
	for(int x=n;x;x--){
		for(int i=1;i<=n;i++)dp[i][i][x]=(1+v[i][i]*dp[i][i][x+1]%mod)%mod;
		for(int len=2;len<=n;len++){
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				dp[i][j][x]=(dp[i+1][j][x]%mod+v[i][j]*dp[i][j][x+1]%mod+v[i][j-1]*dp[i][j-1][x+1]%mod)%mod;
				for(int k=i+1;k<=j-1;k++)if(v[i][k-1])dp[i][j][x]=(dp[i][j][x]+dp[i][k-1][x+1]*dp[k+1][j][x]%mod)%mod;
			}
		}
	}
	for(int i=1;i<=n+1;i++)val[n-i+2]=dp[1][n][i]%mod;
	int ans=0;
	for(int i=1;i<=n+1;i++){
		int up=1,down=1;
		for(int j=1;j<=n+1;j++){
			if(i==j)continue;
			up=up*(c-j+mod)%mod;
			down=down*(i-j+mod)%mod;
		}
		ans=(ans+val[i]%mod*up%mod*qpow(down,mod-2)%mod)%mod;
	}
	cout<<ans%mod;
}