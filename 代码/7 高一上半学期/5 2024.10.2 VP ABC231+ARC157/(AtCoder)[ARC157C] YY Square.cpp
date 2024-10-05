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
	return ans%mod;
}
int fac[N*2],inv[N*2];
void init(int n){
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n-1;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){if(n<0||m<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int dp[2][N][N];
char mp[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int h,w;
	cin>>h>>w;
	init(h+w);
	for(int i=1;i<=h;i++){
		string s;
		cin>>s;
		for(int j=1;j<=w;j++)mp[i][j]=s[j-1]=='Y';
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(mp[i][j]){
				dp[0][i][j]=(dp[0][i-1][j]+dp[0][i][j-1]+(mp[i-1][j]?C(i+j-3,i-2):0)+(mp[i][j-1]?C(i+j-3,i-1):0))%mod;
				dp[1][i][j]=(dp[1][i-1][j]+dp[1][i][j-1]+(mp[i-1][j]?C(i+j-3,i-2)+2*dp[0][i-1][j]:0)+(mp[i][j-1]?C(i+j-3,i-1)+2*dp[0][i][j-1]:0))%mod;
				
			}
			else{			
				dp[0][i][j]=(dp[0][i-1][j]+dp[0][i][j-1])%mod;
				dp[1][i][j]=(dp[1][i-1][j]+dp[1][i][j-1])%mod;
			}
		}
	}
	cout<<dp[1][h][w];
}