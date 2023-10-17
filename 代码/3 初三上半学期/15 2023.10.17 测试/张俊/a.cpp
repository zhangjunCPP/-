#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
const ll mod=998244353;
ll dp[2][N];
int belong[N];

ll solve(int n,int m){
	for(int l=1,r;l<=m;l=r+1){
		r=m/(m/l);
		for(int i=l;i<=r;i++) belong[i]=l;
	}
	memset(dp,0,sizeof dp);
	for(int i=1;i<=m;i++) dp[1][i]=1;
	ll sum=m;
	for(int i=2;i<=n;i++) {
		for(int l=1,r;l<=m;l=r+1){
			r=m/(m/l);
			//求出dp[i][l]
			dp[i&1][l]=sum;
			if(l==1) dp[i&1][l]=1;
			else for(int j=2;j*l<=m;j++) dp[i&1][l]=(dp[i&1][l]-dp[(i-1)&1][belong[j*l]]+mod)%mod;
		}
		sum=0;
		for(int l=1,r;l<=m;l=r+1){
			r=m/(m/l);
			sum=(sum+dp[i&1][l]*(r-l+1)%mod)%mod;
		}
	}
	return sum;
}
signed main(){
	int n,m;
	cin>>n>>m;
	cout<<solve(n,m);
	return 0;
}