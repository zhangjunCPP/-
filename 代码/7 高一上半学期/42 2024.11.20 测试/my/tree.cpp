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
	return ans;
}
int inv(int x){
	return qpow(x,mod-2);
}
signed main(){
	int n;
	cin>>n;
	cout<<n*(n-1)%mod*(n-2)%mod*(n-3)%mod*(n-4)%mod*(n-5)%mod*inv(720)%mod;
}