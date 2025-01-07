#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N];
int dp[N];
int q[N],l,r;
int main(){
	memset(dp,128,sizeof dp);
	dp[0]=0;
	int n,L,R;
	cin>>n>>L>>R;
	for(int i=0;i<=n;i++)cin>>a[i];
	int ans=-0x3f3f3f3f;

	for(int i=L;i<=n;i++){
		//insert(i-L)
		while(l<=r&&dp[i-L]>=dp[q[r]])r--;
		q[++r]=i-L;

		while(l<r&&q[l]<i-R)l++;
		dp[i]=dp[q[l]]+a[i];
		if(i+R>n)ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}