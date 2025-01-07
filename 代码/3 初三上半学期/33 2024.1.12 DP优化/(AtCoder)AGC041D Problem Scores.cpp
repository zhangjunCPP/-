#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int c[N];
int dp[N];
signed main(){
	int n,mod;
	cin>>n>>mod;
	int tmp=n/2;
	for(int i=2;i<=tmp+1;i++) c[i]=i-1;
	for(int i=tmp+2;i<=n;i++) c[i]=n-i+2;
	dp[0]=1;
	for(int i=2;i<=n;i++)for(int j=c[i];j<n;j++)dp[j]=(dp[j]+dp[j-c[i]])%mod;
	int ans=0;
	for(int i=0;i<n;i++)ans=(ans+dp[i]*(n-i)%mod)%mod;
	cout<<ans;
}