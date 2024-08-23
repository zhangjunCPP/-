#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e18;
int a[N];
int dp[2][N];
int sum[N],pre[N],suf[N];
int Max[N];
void solve() {
	int n,m;
	cin>>n>>m;
	sum[0]=pre[0]=suf[m+1]=0;
	Max[0]=-INF;
	for(int i=1;i<=m;i++)dp[0][i]=dp[1][i]=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++)cin>>a[j];
		for(int j=1;j<=m;j++)sum[j]=sum[j-1]+a[j];
		for(int j=1;j<=m;j++)pre[j]=max(0ll,pre[j-1]+a[j]);
		for(int j=m;j>=1;j--)suf[j]=max(0ll,suf[j+1]+a[j]);
		for(int j=1;j<=m;j++)Max[j]=max(Max[j-1],dp[(i-1)&1][j]+pre[j-1]-sum[j-1]);
		int val=-INF;
		for(int j=m;j>=1;j--) {
			dp[i&1][j]=max(sum[j]+suf[j+1]+Max[j],val-sum[j-1]+pre[j-1]);
			val=max(val,dp[(i-1)&1][j]+sum[j]+suf[j+1]);

		}
	}
	int ans=-INF;
	for(int i=1;i<=m;i++)ans=max(ans,dp[n&1][i]);
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}