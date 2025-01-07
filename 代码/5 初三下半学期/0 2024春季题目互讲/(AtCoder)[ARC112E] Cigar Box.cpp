#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+10,mod=998244353;
int fac[N],inv[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int a[N];
int dp[N][N];
signed main(){
	init();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[0][0]=1;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*2*j%mod)%mod;
			dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j])%mod;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		for(int j=n-i;j>=0;j--){
			if(n-i-j>=2&&a[n-j-1]>a[n-j])break;
			ans=(ans+dp[m][i+j]*C(i+j,i)%mod)%mod;
		}
	}
	cout<<ans;
}