#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int x[N],y[N];
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		int up=1,down=1;
		for(int j=1;j<=n;j++){
			if(j==i)continue;
			up=up*(k-x[j]+mod)%mod;
			down=down*(x[i]-x[j]+mod)%mod;
		}
		ans=(ans+y[i]*up%mod*qpow(down,mod-2)%mod)%mod;
	}
	cout<<ans%mod;
}