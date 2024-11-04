#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int dp[2][3][3];
int calc(int x){
	if(x>=0)return x%3;
	return (-2*x)%3;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		x%=3;
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				dp[i&1][j][k]=dp[(i-1)&1][j][k];
			}
		}
		dp[i&1][0][x]=max(dp[i&1][0][x],1);
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				if(calc(x-k)>=j)dp[i&1][calc(x-k)][x]=max(dp[i&1][calc(x-k)][x],dp[(i-1)&1][j][k]+1);
			}
		}

	}
	int ans=2;
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans=max(ans,dp[n&1][i][j]);
	cout<<ans;

}
/*
dp[i][j][k]:考虑前i个数，最后的b_l-b_{l-1} mod 3=j，b_l mod 3=k
 */