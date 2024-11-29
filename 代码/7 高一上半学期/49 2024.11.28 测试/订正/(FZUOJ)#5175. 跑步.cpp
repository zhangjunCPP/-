#include<bits/stdc++.h>
using namespace std;
const int N=100+10;
int m;
int a[N];
int dp[N][N*N];
void solve(){
	int n,k;
	cin>>n>>k;
	int l=0,r=k*m;
	int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(dp[k][mid]<=n)ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<n-ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>m;
	for(int i=1;i<=m;i++)cin>>a[i];
	sort(a+1,a+m+1);
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<100;i++)
		for(int j=0;j<=i*m;j++)
			if(dp[i][j]<0x3f3f3f3f)
				for(int k=0;k<=m;k++)dp[i+1][j+k]=min(dp[i+1][j+k],dp[i][j]+a[k]);
	int q;
	cin>>q;
	while(q--)solve();
}