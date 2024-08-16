#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int INF=1e9;
int dp[N][6];
void solve() {
	string s,t;
	cin>>s>>t;
	dp[0][0]=0,dp[0][1]=dp[0][2]=dp[0][3]=1,dp[0][4]=dp[0][5]=2;
	int n=s.size();
	for(int i=1;i<=n;i++) {
		int tmp0=dp[i-1][0],tmp1=dp[i-1][1],tmp2=dp[i-1][2],tmp3=dp[i-1][3],tmp4=dp[i-1][4],tmp5=dp[i-1][5];
		if(s[i-1]==t[i-1])dp[i][0]=min({tmp0,tmp1,tmp2,tmp3,tmp4,tmp5}),dp[i][3]=INF;
		else dp[i][3]=min({tmp0+1,tmp1+1,tmp2+1,tmp3,tmp4,tmp5}),dp[i][0]=INF;
		if(t[i-1]=='0') {
			dp[i][1]=min({tmp0+1,tmp1,tmp2+1,tmp3+1,tmp4,tmp5+1});
			dp[i][5]=min({tmp0+2,tmp1+2,tmp2+1,tmp3+1,tmp4+1,tmp5});
			dp[i][2]=INF;
			dp[i][4]=INF;
		}
		else {
			dp[i][2]=min({tmp0+1,tmp1+1,tmp2,tmp3+1,tmp4+1,tmp5});
			dp[i][4]=min({tmp0+2,tmp1+1,tmp2+2,tmp3+1,tmp4,tmp5+1});
			dp[i][1]=INF;
			dp[i][5]=INF;
		}
	}
	cout<<min({dp[n][0],dp[n][1],dp[n][2],dp[n][3],dp[n][4],dp[n][5]})<<"\n";
}
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}