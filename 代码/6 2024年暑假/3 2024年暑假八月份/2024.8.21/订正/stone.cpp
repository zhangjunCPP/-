#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=105;
int dp[N][N*N];
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
signed main(){
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	int n,k;
	cin>>n>>k;
	dp[n][1]=n<=k;
	dp[n][0]=k+1-dp[n][1];
	for(int i=n;i>=2;i--) {
		for(int j=0;j<=(n-i+1)*(n-i+1);j++) {
			for(int x=0;x<=k;x++) {//枚举i-1位置上的数
				dp[i-1][j+(x<i)*(x+j)/(i-1)]=(dp[i-1][j+(x<i)*(x+j)/(i-1)]+dp[i][j])%mod;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=k;i++)sum=(sum+i*qpow(k+1,n-1)%mod*n%mod)%mod;
	for(int i=0;i<=n*n;i++)sum=(sum-dp[1][i]*i%mod+mod)%mod;
	cout<<sum;
}
/*
 *优先删前面的，且删前面的不会对后面造成影响，所以可以从后往前DP
 *我们发现，每删一次，总和就减少1，所以我们只需求删的次数即可
 *因此我们可以设dp[i][j]表示i~n删j次的方案数
 *但问题来了，最多删多少次？
 *考虑到我们需要枚举i，枚举每个位置上的值，而可支持的时间复杂度为O(n^4)，因此盲猜最多删O(n^2)次
 *枚举i,j,x，x为i-1位置上的数，相当于x在之前就已经加了j次，而我们已经发现，我们会优先删前面的。
 *所以x在之前已经被删过(x+j)/(i-1)次。
 *那么：dp[i-1][j+(x+j)/(i-1)]<-dp[i][j]
 */