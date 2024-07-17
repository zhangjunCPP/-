#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10,mod=1e8+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int dp1[N],dp2[N];
signed main(){
	int n,m;
	cin>>n>>m;
	dp1[0]=1;
	int tmp=qpow(2,n)-1;
	for(int i=1;i<=m;i++)dp1[i]=dp1[i-1]*(tmp-i+1+mod)%mod;
	dp2[0]=1;
	for(int i=2;i<=m;i++)dp2[i]=(dp1[i-1]-dp2[i-1]+mod-dp2[i-2]*(i-1)%mod*(tmp-(i-2)+mod)%mod+mod)%mod;
	int tmp2=1;
	for(int i=1;i<=m;i++)tmp2=tmp2*i%mod;
	cout<<dp2[m]*qpow(tmp2,mod-2)%mod;
}