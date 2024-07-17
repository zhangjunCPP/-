#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10;
const int mod=1e9+7;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int inv[N];
void init() {
	inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}
int C(int n,int m) {
	n%=mod;
	if(m<0||n<0||m>n)return 0;
	if(m==0||n==m)return 1;
	int ans=1;
	for(int i=n-m+1;i<=n;i++)ans=ans*i%mod;
	for(int i=1;i<=m;i++)ans=ans*inv[i]%mod;
	return ans%mod;
}
int f[N];
signed main() {
	init();
	int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>f[i];
	int ans=0;
	for(int S=0;S<(1<<n);S++) {
		int sum=0;
		int tot=__builtin_popcount(S);
		for(int i=1;i<=n;i++)if((S>>(i-1))&1)sum+=f[i];
		ans=(ans+(tot&1?-1:1)*C(n+s-sum-tot-1,n-1)%mod+mod)%mod;
	}
	cout<<ans%mod;
}