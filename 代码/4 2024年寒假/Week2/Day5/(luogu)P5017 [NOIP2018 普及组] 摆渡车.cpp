#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int sum1[N],sum2[N];
int dp[N];
signed main() {
	int n,m;
	cin>>n>>m;
	int t=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		t=max(t,x);
		sum1[x]++;
		sum2[x]+=x;
	}
	for(int i=1;i<t+m;i++)sum1[i]+=sum1[i-1],sum2[i]+=sum2[i-1];
	for(int i=1;i<t+m;i++){
		dp[i]=sum1[i]*i-sum2[i];
		for(int j=max(i-2*m+1,0ll);j<=i-m;j++)dp[i]=min(dp[i],dp[j]+i*(sum1[i]-sum1[j])-(sum2[i]-sum2[j]));
	}
	int ans=0x3f3f3f3f;
	for(int i=t;i<t+m;i++)ans=min(ans,dp[i]);
	cout<<ans;
	return 0;
}