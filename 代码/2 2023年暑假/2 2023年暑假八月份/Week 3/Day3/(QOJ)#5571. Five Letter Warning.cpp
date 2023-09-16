#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[4][130][130]; 
int a[2000000];
signed main(){
	string s;
	int mod;
	cin>>s>>mod;
	int n=s.size();
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=33;j<=126;j++)ans=(ans+dp[3][s[i]][j])%mod;
		for(int j=33;j<=126;j++)dp[3][j][s[i]]=(dp[3][j][s[i]]+dp[2][j][s[i]]-dp[1][j][s[i]]*(n-i+1)%mod+mod)%mod;
		for(int j=33;j<=126;j++)dp[2][j][s[i]]=(dp[2][j][s[i]]+dp[0][j][0]*(n-i)%mod+mod)%mod;
		for(int j=33;j<=126;j++)dp[1][j][s[i]]=(dp[1][j][s[i]]+dp[0][j][0])%mod;
		dp[0][s[i]][0]=(dp[0][s[i]][0]+1)%mod;
	}
	cout<<ans%mod;

	return 0;
}

