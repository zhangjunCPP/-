#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+10,INF=1e18;
int f[N];
int dp[2][3000];
signed main(){
	int s,n,p1,q1,p2,q2;
	cin>>s>>n>>p1>>q1>>p2>>q2;
	int ans=s;
	for(int i=n;i;i--)f[i]=f[i+1]+max(0ll,q1*(n-i)-p1)+max(0ll,q2*(n-i)-p2);
	for(int i=0;i<3000;i++)dp[0][i]=dp[1][i]=-INF;
	dp[0][0]=s;
	int S=10000;
	S=min(S,n);
	for(int i=0;i<S;i++){
		int tmp=i&1;
		for(int j=0;j<p1+p2;j++){
			if(dp[tmp][j]==-INF)continue;
			dp[tmp^1][j]=max(dp[tmp^1][j],dp[tmp][j]+j);
			ans=max(ans,dp[tmp][j]+j*(n-i));
			if(dp[tmp][j]>=p1+p2){
				if(j+q1+q2<p1+p2)dp[tmp^1][j+q1+q2]=max(dp[tmp^1][j+q1+q2],dp[tmp][j]-p1-p2+q1+q2+j);
				else ans=max(ans,dp[tmp][j]-p1-p2+(n-i)*(j+q1+q2)+f[i+1]);
			}
			if(dp[tmp][j]>=p1){
				if(j+q1<p1+p2)dp[tmp^1][j+q1]=max(dp[tmp^1][j+q1],dp[tmp][j]-p1+q1+j);
				else ans=max(ans,dp[tmp][j]-p1+(n-i)*(j+q1)+f[i+1]);
			}
			if(dp[tmp][j]>=p2){
				if(j+q2<p1+p2)dp[tmp^1][j+q2]=max(dp[tmp^1][j+q2],dp[tmp][j]-p2+q2+j);
				else ans=max(ans,dp[tmp][j]-p2+(n-i)*(j+q2)+f[i+1]);
			}
			dp[tmp][j]=-INF;
		}
	}
	cout<<ans;
}