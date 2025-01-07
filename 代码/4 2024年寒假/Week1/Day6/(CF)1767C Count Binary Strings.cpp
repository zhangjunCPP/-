#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=105;
int a[N][N];
int dp[N][N];
bool flag[N];
int last[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) last[i]=1;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) {
			cin>>a[i][j];
			if(a[i][j]==1)for(int k=i+1;k<=j;k++) flag[k]=true;
			else if(a[i][j]==2)last[j]=max(last[j],i+1);
		}
		if(a[i][i]==2){
			puts("0");
			return 0;
		}
	}
	dp[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=last[i];j<i;j++) dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
		if(!flag[i]) for(int j=1;j<i;j++) dp[i][i]=(dp[i][i]+dp[i-1][j])%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+dp[n][i])%mod;
	cout<<ans*2%mod;
}