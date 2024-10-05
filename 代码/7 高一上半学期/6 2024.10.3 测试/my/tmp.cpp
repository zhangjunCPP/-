#include<bits/stdc++.h>
using namespace std;
const int N=5000+10;
int dp[N][N],dp2[N][N];
int sum[N][N];
int main(){
	int k,v;
	cin>>k>>v;
	for(int i=1;i<=v;i++)dp[1][i]=i,sum[1][i]=sum[1][i-1]+dp[1][i];
	// dp[0][0]=1;
	for(int i=2;i<=k;i++){
		for(int j=i;j<=v;j++){
			dp[i][j]+=sum[i-1][j-1];
			if(i>2)dp2[i][j]+=dp2[i][j-1]+dp[i-2][j-2];
			else dp2[i][j]=dp[i][j]-dp[i][j-1];
			sum[i][j]=sum[i][j-1]+dp[i][j];
		}
	}
	// cout<<dp[k][v]<<" "<<dp2[k][v];
}
