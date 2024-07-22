#include<bits/stdc++.h>
using namespace std;
const long long p=998244353;
const long long maxn=1e6+5;
long long ksm(long long a,long long b,long long p){
	long long ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%p;
		b>>=1,a=1ll*a*a%p;
	}
	return ans;
}
long long fac[maxn],inv[maxn];
long long C(long long n,long long m){
	if(n<0||m<0) return 0;
	if(n<m) return 0;
	return 1ll*fac[n]*inv[m]%p*inv[n-m]%p;
}
int main(){
	freopen("trade.in", "r",stdin);
	freopen("trade.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	long long tp;cin>>tp;
	long long n,K;
	if(tp==1) cin>>n>>K;
	else cin>>n;
	fac[0]=inv[0]=1;
	for(long long i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%p;
	inv[n]=ksm(fac[n],p-2,p);
	for(long long i=n-1;i>=1;--i) inv[i]=1ll*inv[i+1]*(i+1)%p;		
	long long ans=0;
	if(tp==1){
		cout<<1ll*(n+1-2*K)%p*(C(n,K)-C(n,K-1)+p)%p<<'\n';
	}
	else{
		for(long long i=0;i<=n/2;++i){
			ans=(ans+1ll*ksm(233,i,p)*(n+1-2*i)%p*(C(n,i)-C(n,i-1)+p)%p)%p;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
