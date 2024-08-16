#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[2][205][2];
//dp[k][i][0]:在第k个音符落下时，左手接住，右手在i位置
//dp[k][i][1]:在第k个音符落下时，右手接住，左手在i位置
int n,m;
int dis(int i,int j) {
	int tmp=max(i,j)-min(i,j);
	return min(tmp,n-tmp);
}
signed main() {
	freopen("cisum.in","r",stdin);
	freopen("cisum.out","w",stdout);
	cin>>n>>m;
	int lasttime=0,lastpos=0;
	memset(dp,128,sizeof dp);
	dp[0][0][0]=dp[0][0][1]=0;
	for(int k=1;k<=m;k++) {
		int t,x;
		cin>>t>>x;
		int tmp=t-lasttime;
		for(int i=0;i<n;i++) {
			dp[k&1][i][0]=dp[(k-1)&1][i][0];
			for(int j=0;j<n;j++) {
				int dis1=dis(x,lastpos),dis2=dis(i,j);
				int dis3=dis(x,j),dis4=dis(lastpos,i);
				if(dis1<=tmp&&dis2<=tmp)dp[k&1][i][0]=max(dp[k&1][i][0],dp[(k-1)&1][j][0]+1);
				if(dis3<=tmp&&dis4<=tmp)dp[k&1][i][0]=max(dp[k&1][i][0],dp[(k-1)&1][j][1]+1);
				if(dis3<=tmp&&dis4<=tmp)dp[k&1][i][1]=max(dp[k&1][i][1],dp[(k-1)&1][j][0]+1);
				if(dis1<=tmp&&dis2<=tmp)dp[k&1][i][1]=max(dp[k&1][i][1],dp[(k-1)&1][j][1]+1);
			}
		}
		lasttime=t,lastpos=x;
	}
	int ans=0;
	for(int i=0;i<n;i++)ans=max({ans,dp[m&1][i][0],dp[m&1][i][1]});
	cout<<ans;
}