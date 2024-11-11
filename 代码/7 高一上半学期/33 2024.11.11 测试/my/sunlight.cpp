#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
int dp[2][N][N];
int main(){
	int s,n,p1,q1,p2,q2;
	cin>>s>>n>>p1>>q1>>p2>>q2;
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[0][i][j]=dp[1][i][j]=-1;
	dp[0][0][0]=s;
	int sum=p1+p2;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=i;k++){
				int tmp=dp[(i-1)&1][j][k];
				if(j&&dp[(i-1)&1][j-1][k]>=p1)tmp=max(tmp,dp[(i-1)&1][j-1][k]-p1);
				if(k&&dp[(i-1)&1][j][k-1]>=p2)tmp=max(tmp,dp[(i-1)&1][j][k-1]-p2);
				if(j&&k&&dp[(i-1)&1][j-1][k-1]>=sum)tmp=max(tmp,dp[(i-1)&1][j-1][k-1]-sum);
				if(tmp!=-1)dp[i&1][j][k]=tmp+j*q1+k*q2;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)ans=max(ans,dp[n&1][i][j]);
	cout<<ans;
}