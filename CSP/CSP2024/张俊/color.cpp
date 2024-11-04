#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10,M=2000+10;
int a[N];
int sum[M][M];
int dp[N][N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		sum[i][i]=0;
		for(int j=i-1;j;j--){
			//[l,r] have the same color
			sum[i][j]=sum[i][j+1]+(a[j]==a[j+1]?a[j+1]:0);
		}
	}
	for(int i=1;i<=n;i++){
		dp[i][i]=sum[i][i];
		for(int j=1;j<i;j++){
			for(int k=0;k<j;k++){
				dp[i][j+1]=max(dp[i][j+1],dp[j][k+1]+sum[i][j+1]+(a[j+1]==a[k]?a[j+1]:0));
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=max({ans,dp[n][i]});
	cout<<ans<<"\n";
}
signed main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}