#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+5,mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int a[105];
int sum[105];
int dp[N];
int tmp[105];
signed main(){
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		a[i]=x*qpow(y,mod-2)%mod;
	}
	a[++k]=1;
	sum[0]=1;
	for(int i=1;i<=k;i++)sum[i]=sum[i-1]*(1-a[i-1]+mod)%mod;
	for(int i=1;i<=k;i++)tmp[i]=sum[i]*a[i]%mod;
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i&&j<=k;j++)dp[i]=(dp[i]+tmp[j]*dp[i-j]%mod)%mod;
		dp[i]++;
	}
	cout<<(dp[n]-1+mod)%mod;
}