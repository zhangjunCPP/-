#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10,mod=998244353;
int a[N];
int dp[N];
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<=n;i++)cin>>a[i];
	dp[0]=1;
	for(int S=0;S<(1<<n)-1;S++){
		int sum=a[0];
		for(int i=1;i<=n;i++)if(S&(1<<(i-1)))sum+=a[i];
		for(int i=1;i<=n;i++){
			if(S&(1<<(i-1)))continue;
			if(sum>=a[i]){
				int T=S|(1<<(i-1));
				dp[T]=(dp[T]+dp[S])%mod;
			}
		}
	}
	cout<<dp[(1<<n)-1];
}
