#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
signed main(){
	int n,m;
	cin>>n>>m;
	int ans=qpow(2*n+2,m);
	ans=ans*(n+1-m+mod)%mod*qpow(n+1,mod-2)%mod;
	cout<<ans;
}