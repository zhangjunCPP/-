#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e3+10;
int n,m;
int a[N],b[N];
ll dp[N][N];
bool check(int mid){
	dp[0][0]=0;
	for(int i=1;i<=m;i++) dp[0][i]=-1e9;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=m;j++) {
			dp[i][j]=-1e9;
			for(int k=max(0,j-mid/a[i]);k<=j;k++){
				dp[i][j]=max(dp[i][j],dp[i-1][k]+(mid-a[i]*(j-k))/b[i]);
			}
		}
	}
	return dp[n][m]>=m;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	ll l=1,r=1e9+10;
	ll ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}
