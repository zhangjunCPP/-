#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int dp[N][2];
void solve(){
	int n;
	cin>>n;
	for(int i=0;i<=n;i++)dp[i][0]=dp[i][1]=0;
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		dp[x+1][0]=(2*dp[x+1][0]+dp[x][0])%mod;
		dp[x+1][1]=(2*dp[x+1][1])%mod;
		if(x)dp[x-1][1]=(2*dp[x-1][1]+dp[x-1][0])%mod;
	}
	int ans=0;
	for(int i=0;i<=n;i++)ans=(ans+dp[i][0]+dp[i][1])%mod;
	cout<<(ans-1+mod)%mod<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}