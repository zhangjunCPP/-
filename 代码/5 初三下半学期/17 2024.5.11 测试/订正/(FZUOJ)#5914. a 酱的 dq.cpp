#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=2e7+10;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int inv[N],fac[N];
int pw[N];
void init(int n){
	fac[0]=pw[0]=inv[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2)%mod;
	for(int i=n-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){if(m>n)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	int n;
	cin>>n;
	init(n*2);
	int ans=0;
	for(int i=1;i<=n;i++){
		int tmp=(C(n+i-2,n-1)-C(n+i-2,n)+mod)%mod;
		ans=(ans+tmp*pw[max(0ll,n-i-1)]%mod)%mod;
	}
	cout<<ans;
}