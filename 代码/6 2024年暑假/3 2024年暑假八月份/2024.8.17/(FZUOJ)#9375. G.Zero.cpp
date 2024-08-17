#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mo=998244353, maxn=1e5+5, N=1e5, inv2=499122177;

char a[maxn];
ll b[maxn][31], c[maxn][31];
ll f[maxn], g[maxn], s[maxn], C[33][33];

ll qpow(ll a,ll p) {
	ll res=1;
	while(p) {
		if(p&1) res=res*a%mo;
		p>>=1, a=a*a%mo;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll n,k; cin>>n>>k;
	for(ll i=0;i<=k;i++) {
		for(ll j=0;j<=i;j++) {
			if(!j||i==j) C[i][j]=1;
			else C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
		}
	}
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=n+1;i++) {
		ll pw=1;
		b[i][0]=1;
		for(ll j=1;j<=k;j++) {
			pw=pw*(mo-i)%mo;
			b[i][j]=pw*C[k][j]%mo;
		}
		pw=1;
		for(ll j=k;j>=0;j--) {
			c[i][j]=pw;
			pw=pw*i%mo;
		}
	}
	ll ans=0;
	for(ll t=0;t<=k;t++) {
		memset(f,0,sizeof(f)), memset(g,0,sizeof(g)), memset(s,0,sizeof(s));
		s[0]=1;
		for(ll i=1;i<=n;i++) {
			if(a[i]!='1') (s[i]+=s[i-1])%=mo, (f[i]+= f[i-1])%=mo;
			if(a[i]!='0') {
				(s[i]+= s[i-1])%=mo, (f[i]+= f[i-1])%=mo, (g[i]+= g[i-1])%=mo;
				(f[i]+= (g[i-1]+s[i-1]*b[i][t]%mo)%mo*c[i+1][t]%mo)%=mo; 
				(g[i]+= s[i-1]*b[i][t]%mo)%=mo;
			}
		}
		(ans+= f[n])%=mo;
	}
	ll pw=1;
	for(ll i=1;i<=n;i++) if(a[i]=='?') pw=pw*inv2%mo;
	cout<<ans*pw%mo<<'\n';
	return 0;
}