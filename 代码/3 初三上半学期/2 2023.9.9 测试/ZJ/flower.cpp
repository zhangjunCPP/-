#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int INF=3e18+10;
int dp[N];
signed main(){
	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout); 
	int n,A,B,C,D;
	cin>>n>>A>>B>>C>>D;
	for(int i=0;i<N;i++) dp[i]=INF;
	dp[0]=0;
	for(int i=1;i<=n+max(A,C);i++){
		if(i>=A) dp[i]=min(dp[i],dp[i-A]+B);
		if(i>=C) dp[i]=min(dp[i],dp[i-C]+D);
	}
	int ans=INF;
	for(int i=n;i<=n+max(A,C);i++) ans=min(ans,dp[i]);
	cout<<ans;
	return 0;
}

