#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e3+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int pw[N];
int dp[N];
signed main(){
	int n,m;
	string s;
	cin>>n>>m>>s;
	
	pw[0]=1;
	for(int i=1;i<=m;i++)pw[i]=pw[i-1]*n%mod;
	for(int i=1;i<=n;i++){
		int sum=1;
		for(int j=1;j<=m;j++){
			int tmp;
			if(s[j-1]=='=')tmp=1;
			else if(s[j-1]=='<')tmp=n-i;
			else tmp=i-1;
			dp[j]=(dp[j]+tmp*sum%mod*pw[m-j]%mod)%mod;
			sum=sum*(n-tmp)%mod;
		}
		dp[m+1]=(dp[m+1]+sum)%mod;
	}
	int inv=qpow(pw[m],mod-2);
	for(int i=1;i<=m+1;i++)cout<<(dp[i]*inv)%mod<<" ";
}