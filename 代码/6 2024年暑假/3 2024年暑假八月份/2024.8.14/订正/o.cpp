#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=150+10;
const int INF=1e9;
int a[N];
int f[N][N],g[N][N][N];
int dp[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	memset(f,128,sizeof f);
	memset(g,128,sizeof g);
	memset(dp,128,sizeof dp);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==-1)a[i]=-INF;
	}
	string s;
	cin>>s;
	for(int i=1;i<=n;i++){
		f[i][i]=a[1];
		g[i][i][0]=a[1];
		g[i][i][1]=0;
		dp[i][i]=max(0ll,a[1]);
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(int k=1;k<=len;k++){
				for(int p=l;p<r;p++)g[l][r][k]=max({g[l][r][k],g[l][p][k]+f[p+1][r],f[l][p]+g[p+1][r][k]});
				if(s[l-1]==s[r-1]){
					if(len==2)g[l][r][k]=max(0ll,g[l][r][k]);
					else g[l][r][k]=max(g[l][r][k],g[l+1][r-1][k-2]);
				}
				f[l][r]=max(f[l][r],g[l][r][k]+a[k]);
			}
			g[l][r][0]=f[l][r];
			dp[l][r]=max(0ll,f[l][r]);
			for(int k=l;k<r;k++)dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
		}
	}
	cout<<dp[1][n]<<" ";
	return 0;
}