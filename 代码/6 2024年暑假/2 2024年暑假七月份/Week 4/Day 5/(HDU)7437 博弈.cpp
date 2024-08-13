#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=998244353;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
const int inv2=qpow(2,mod-2);
int fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2)%mod;
	for(int i=N-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int a[N];
void solve() {
	int n;
	cin>>n;
	int sum=0;
	int tot=0;
	for(int i=1;i<=n;i++) {
		char ch;
		cin>>ch>>a[i];
		sum+=a[i];
		tot+=(a[i]&1);
	}
	if(tot>=2){cout<<inv2<<"\n";return;}
	int ans=1;
	ans=ans*inv[sum]%mod*fac[sum/2]%mod;
	for(int i=1;i<=n;i++)ans=ans*fac[a[i]]%mod*inv[a[i]/2]%mod;
	cout<<(tot?(1+ans)*inv2%mod:(1-ans+mod)*inv2%mod)<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}