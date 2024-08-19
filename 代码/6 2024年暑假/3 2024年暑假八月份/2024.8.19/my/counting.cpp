#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000+10,mod=998244353;
int a[N][N];
bitset<N>mp[20];
int fac[N],inv[N];
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m) {
	if(m>n)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main() {
	freopen("counting.in","r",stdin);
	freopen("counting.out","w",stdout);
	init();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)mp[j].set(i,a[i][j]);
	int ans=0;
	for(int s=0;s<(1<<m);s++) {
		bitset<N>tmp;
		for(int i=1;i<=m;i++)if((s>>(i-1))&1)tmp^=mp[i];
		int sum=tmp.count();
		for(int i=1;i<=sum;i+=2)ans=(ans+qpow(2,n-sum)*C(sum,i))%mod;
	}
	cout<<ans;
}