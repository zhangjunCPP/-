#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
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
int fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2)%mod;
	for(int i=N-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m) {
	if(m>n)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void solve() {
	int n,m,k;
	cin>>n>>m>>k;
	if(k>n||k>m){puts("0");return;}
	cout<<(C(n+m,k)-C(n+m,k-1)+mod)%mod<<"\n";
}
signed main() {
	init();
	int T;
	cin>>T;
	while(T--)solve();
}