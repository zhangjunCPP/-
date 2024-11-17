#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3000+10,mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int inv[N];
int dp[N][N*2],sum[N][N*2];
void init(){
	inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	dp[0][0]=1;
	sum[0][0]=1;
	for(int i=1;i<N;i++){
		dp[i][0]=inv[i+1]*dp[i-1][0]%mod;
		for(int j=1;j<=min(i*(i+1)/2,2*N-1);j++){
			dp[i][j]=inv[i+1]*(sum[i-1][(min({j,(i-1)*i/2,2*N-1}))]-(j-i-1>=0?sum[i-1][j-i-1]:0)+mod)%mod;
		}
		sum[i][0]=dp[i][0];
		for(int j=1;j<=min(i*(i+1)/2,2*N-1);j++)sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
	}
}
void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	int take=n*m/k;
	cout<<(1-sum[n][take]+mod)%mod<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}