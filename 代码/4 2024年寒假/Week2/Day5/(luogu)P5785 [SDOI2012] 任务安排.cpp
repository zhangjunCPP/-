#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,s;
int sum1[N],sum2[N];
int q[N];
int dp[N];
int l,r;
int erfen(int val){
	if(l==r) return q[l];
	int L=l,R=r;
	while(L<R){
		int mid=(L+R)>>1;
		if((dp[q[mid+1]]-dp[q[mid]])<=val*(sum2[q[mid+1]]-sum2[q[mid]])) L=mid+1;
		else R=mid;
	}
	return q[L];
}
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		int t,c;
		cin>>t>>c;
		sum1[i]=sum1[i-1]+t;
		sum2[i]=sum2[i-1]+c;
	}
	l=1,r=1;
	q[1]=0;
	for(int i=1;i<=n;i++){
		int p=erfen(s+sum1[i]);
		dp[i]=dp[p]-(s+sum1[i])*sum2[p]+sum1[i]*sum2[i]+s*sum2[n];
		while(l<r&&(dp[q[r]]-dp[q[r-1]])*(sum2[i]-sum2[q[r]])>=(dp[i]-dp[q[r]])*(sum2[q[r]]-sum2[q[r-1]]))r--;
		q[++r]=i;
	}
	cout<<dp[n];
}