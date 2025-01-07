#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=3e5+5, mo=998244353;

ll n,k;
ll p[maxn], pw[maxn], pw2[maxn], ed[maxn], vis[maxn];
ll fac[maxn], ifac[maxn], ans[maxn], sum[maxn];

vector<ll> op[maxn];

struct BIT {
	ll bit[maxn];
	ll lowbit(ll x) {
		return x&(-x);
	}
	void add(ll x,ll v) {
		for(ll i=x;i<=n;i+=lowbit(i)) (bit[i]+= v)%= mo;
		return ;
	}
	ll ask(ll x) {
		ll res=0;
		for(ll i=x;i>0;i-=lowbit(i)) res+= bit[i];
		return res%mo;
	}
}B1,B2,B3;

ll qpow(ll a,ll p) {
	ll res=1;
	while(p) {
		if(p&1) res=res*a%mo;
		p>>=1, a=a*a%mo;
	}
	return res;
}

ll C(ll n,ll m) {
	if(n<0||m<0||n<m) return 0;
	return fac[n]*ifac[m]%mo*ifac[n-m]%mo;
}

int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>k;
	pw[0]=pw2[0]=fac[0]=1;
	for(ll i=1;i<=n;i++) pw[i]=pw[i-1]*n%mo, pw2[i]=pw2[i-1]*(n-1)%mo, fac[i]=fac[i-1]*i%mo;
	ifac[n]=qpow(fac[n],mo-2);
	for(ll i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mo;
	for(ll i=1;i<=k;i++) cin>>p[i];
	for(ll i=1;i<=n;i++) ed[i]=k+1;
	for(ll i=n;i>=1;i--) ed[p[i]]=i;
	for(ll i=1;i<=n;i++) op[ed[i]].push_back(i);
	for(ll i=1;i<=n;i++) B3.add(i,1);
	for(ll i=1;i<=k;i++) {
		ll c=B3.ask(p[i]);
		sum[i]=sum[i-1];
		if(c>1) {
			(sum[i]+= (c-1)*C(n-i,k-i)%mo*fac[k-i]%mo)%= mo;
			B1.add(p[i],(C(n-i,k-i)*fac[k-i]%mo+(c-2)*fac[k-i]%mo*C(n-i-1,k-i-1)%mo)%mo);
			B2.add(p[i],(c-1)*fac[k-i]%mo*C(n-i-1,k-i-1)%mo);
		}
		(ans[p[i]]+= B1.ask(n)-B1.ask(p[i])+mo)%= mo;
		(ans[p[i]]+= B2.ask(p[i]))%= mo;
		B3.add(p[i],-1);
	}
	for(auto x:op[k+1]) {
		(ans[x]+= B1.ask(n)-B1.ask(x)+mo)%= mo;
		(ans[x]+= B2.ask(x))%= mo;
	}
	for(ll i=1;i<=k;i++) ans[p[i]]=(ans[p[i]]+sum[k]-sum[i]+1+mo)%mo;
	for(ll i=1;i<=n;i++) cout<<ans[i]<<'\n';
	return 0;
}