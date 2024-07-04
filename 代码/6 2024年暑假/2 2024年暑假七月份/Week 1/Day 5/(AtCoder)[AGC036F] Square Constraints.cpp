#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500+10;
int n,mod;
pair<int,int> a[N];
int dp[N][N];
int solve(int k){
	memset(dp,0,sizeof dp);
	dp[0][0]=1;
	int c1=0,c2=0;
	for(int i=1;i<=2*n;i++){
		if(!a[i].second){
			for(int j=0;j<=c2;j++)dp[i][j]=(dp[i][j]+dp[i-1][j]*(a[i].first+1-j-c1)%mod)%mod;
			c1++;
		}
		else{
			for(int j=0;j<=c2;j++){
				dp[i][j+1]=(dp[i][j+1]+dp[i-1][j]*(a[i].first-c1-j+1)%mod)%mod;
				dp[i][j]=(dp[i][j]+dp[i-1][j]*(a[i].second+1-n-k-c2+j)%mod)%mod;
			}
			c2++;
		}
	}
	return dp[2*n][k];
}
signed main(){
	cin>>n>>mod;
	for(int i=0;i<n;i++){
		a[i+1].first=ceil(sqrt(n*n-i*i))-1;
		a[i+1].second=min((int)floor(sqrt(4*n*n-i*i)),2*n-1);
	}
	for(int i=n;i<2*n;i++){
		a[i+1].first=min((int)floor(sqrt(4*n*n-i*i)),2*n-1);
		a[i+1].second=0;
	}
	sort(a+1,a+2*n+1);
	int ans=0;
	for(int i=0;i<=2*n;i++)ans=(ans+(i&1?-solve(i):solve(i))+mod)%mod;
	cout<<ans;
}