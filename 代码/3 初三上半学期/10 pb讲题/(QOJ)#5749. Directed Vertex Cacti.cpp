#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=1e9+9;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int C(int x,int y){
	int ans1=1,ans2=1;
	for(int i=y;i>=1;i--) {
		ans2=ans2*i%mod;
		ans1=ans1*(x-i+1)%mod;
	}
	return ans1*qpow(ans2,mod-2)%mod;
}
signed main(){
	int n,m;
	cin>>n>>m;
	int ans=1;
	for(int i=1;i<=n;i++) ans=ans*i%mod;
	ans=ans*C(C(n,2)%mod,m)%mod;
	cout<<ans;
	return 0;
}
