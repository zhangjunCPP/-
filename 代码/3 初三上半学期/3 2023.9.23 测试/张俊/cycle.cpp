#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
signed main() {
	freopen("cycle.in","r",stdin);
	freopen("cycle.out","w",stdout);
	int n;
	cin>>n;
	int ans=qpow(2,n)%mod;
	cout<<ans;
}
