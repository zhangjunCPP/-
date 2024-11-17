#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000+10,INF=1e9,mod=998244353;
int n;
int a[N],b[N];
int unknown[N],tot;
int ans;
int dp[N][3];
int calc(){
	for(int i=1;i<=n;i++)dp[i][0]=dp[i][1]=dp[i][2]=-INF;
	dp[0][0]=dp[0][1]=dp[0][2]=0;
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			dp[i][0]=max(dp[i-1][1],dp[i-1][2]);
			dp[i][1]=max(dp[i-1][2],dp[i-1][0])+1;
		}
		else if(a[i]==1){
			dp[i][1]=max(dp[i-1][2],dp[i-1][0]);
			dp[i][2]=max(dp[i-1][1],dp[i-1][0])+1;
		}
		else{
			dp[i][2]=max(dp[i-1][1],dp[i-1][0]);
			dp[i][0]=max(dp[i-1][2],dp[i-1][1])+1;
		}
	}
	return max({dp[n][0],dp[n][1],dp[n][2]});

}
void dfs(int k){
	if(k>tot){
		ans=(ans+calc())%mod;
		return;
	}
	for(int i=0;i<=2;i++){
		a[unknown[tot]]=i;
		dfs(k+1);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==-1)unknown[++tot]=i;
	}
	dfs(1);
	cout<<ans;
}