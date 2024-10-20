#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=998244353;
int fac[N],inv[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int w[N],a[N];
int dp[N][35][2];

signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int n,m,c;
	cin>>n>>m>>c;
	for(int i=1;i<=n+1;i++)cin>>w[i];
	int INV=1;
	for(int i=1;i<=c;i++)cin>>a[i],INV=INV*inv[a[i]]%mod;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(i)dp[i][j][0]=(dp[i-1][j][0]+dp[i-1][j][1])%mod;
			if(j)dp[i][j][1]=(dp[i][j-1][0]+dp[i][j-1][1]+(j==1?w[i+j]:0))%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=c;i++){
		for(int j=1;j<=a[i];j++){
			int val;
			cin>>val;
			int tmp1,tmp2;
			tmp1=INV*fac[n-j]%mod*fac[a[i]]%mod*inv[a[i]-j]%mod;
			if(j==a[i])tmp2=tmp1;
			else tmp2=(tmp1-INV*fac[n-j-1]%mod*fac[a[i]]%mod*inv[a[i]-j-1]%mod+mod)%mod;
			ans=(ans+dp[n-j][m][1]*tmp1%mod*val%mod+dp[n-j][m][0]*tmp2%mod*val%mod)%mod;
		}
	}
	ans=(ans+INV*fac[n]%mod*dp[n][m][1]%mod)%mod;
	cout<<ans;
}