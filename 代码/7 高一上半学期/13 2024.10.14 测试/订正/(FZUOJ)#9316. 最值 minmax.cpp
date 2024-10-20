#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10;
const int mod=998244353;
int n;
int a[N];
int dp[2][N],sum[2][N];
void solve(){
	int ans=0;
	for(int i=n;i;i--)dp[1][i]=(a[i]+mod)%mod,sum[1][i]=(sum[1][i+1]+dp[1][i])%mod;
	for(int i=2;i<=n;i++){
		for(int j=n-i+2;j;j--){
			dp[i&1][j]=(dp[(i-1)&1][j]*(n-j+1-i+1)%mod+sum[(i-1)&1][j+1]%mod)*a[j]%mod;
			sum[i&1][j]=(sum[i&1][j+1]+dp[i&1][j])%mod;
		}
		for(int j=1;j<=n;j++)dp[(i-1)&1][j]=sum[(i-1)&1][j]=0;
	}
	for(int j=n-n+2;j;j--)ans=(ans+dp[n&1][j]+mod)%mod;
	cout<<ans<<" ";
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);solve();
	reverse(a+1,a+n+1);solve();
}