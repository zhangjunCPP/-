#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[105][105];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int q;
	cin>>q;
	while(q--){
		int t,x,y;
		cin>>t>>x>>y;
		if(t<x+y){puts("NO");continue;}
		memset(dp,0,sizeof dp);
		dp[0][0]=t-x-y+1;
		for(int i=0;i<=x;i++)for(int j=0;j<=y;j++)dp[i][j+1]+=(dp[i][j]+1)/2,dp[i+1][j]+=dp[i][j]/2;
		int tmp1=dp[x][y];
		memset(dp,0,sizeof dp);
		dp[0][0]=t-x-y;
		for(int i=0;i<=x;i++)for(int j=0;j<=y;j++)dp[i][j+1]+=(dp[i][j]+1)/2,dp[i+1][j]+=dp[i][j]/2;
		int tmp2=dp[x][y];
		if(tmp1==tmp2)puts("NO");
		else puts("YES");
	}
	return 0;
}