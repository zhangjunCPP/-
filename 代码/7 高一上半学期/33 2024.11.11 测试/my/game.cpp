#include<bits/stdc++.h>
#define int long long
using namespace std;
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
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int a,b;
	cin>>a>>b;
	cout<<a*qpow(a+b,mod-2)%mod;
}