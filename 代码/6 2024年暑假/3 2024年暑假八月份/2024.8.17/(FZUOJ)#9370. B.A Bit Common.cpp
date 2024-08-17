#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mo;
ll c[5005][5005], pw[5005];

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
	ll n,m; cin>>n>>m>>mo;
	for(ll i=0;i<=n;i++) {
		for(ll j=0;j<=i;j++) {
			if(!j||i==j) c[i][j]=1;
			else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
		}
	}
	pw[0]=1;
	for(ll i=1;i<=max(n,m);i++) pw[i]=pw[i-1]*2%mo;
	ll ans=0;
	for(ll i=1;i<=n;i++) (ans+= c[n][i]*qpow(pw[m-1],n-i)%mo*qpow(pw[i]-1,m-1)%mo)%=mo;
	cout<<ans<<'\n';
	return 0;
} 