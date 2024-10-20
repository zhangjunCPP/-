#include<bits/stdc++.h>
#define fi first
#define se second
#define il inline
using namespace std;
#define ll long long
#define INT __int128
#define ld long double
#define pb emplace_back
#define lb(x) ((x)&-(x))
#define pii pair<int,int>
#define ull unsigned long long
#define TIME clock()*1.0/CLOCKS_PER_SEC
il int pc(int x){return __builtin_popcount(x);}
il int pc(ll x){return __builtin_popcountll(x);}
template<typename T> il void chkmin(T& x,T y){if(x>y)x=y;}
template<typename T> il void chkmax(T& x,T y){if(x<y)x=y;}
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
#define rand(x,y) uniform_int_distribution<ll>(x,y)(rng)
#ifndef ONLINE_JUDGE
#define debug(x) (cerr<<#x<<": "<<x<<endl)
void __file(string s){freopen((s+".in").c_str(),"r",stdin),freopen((s+".out").c_str(),"w",stdout);}
#undef DEBUG
#define DEBUG cerr<<"Passing ["<<__FUNCTION__<<"] in LINE "<<__LINE__<<endl
#else
#define debug(x) 0
#define __file(s) 0
#define DEBUG 0
#endif
const ll P=998244353;
ll qpow(ll x,ll y=P-2){ll z=1;while(y){if(y&1)z=z*x%P;x=x*x%P,y>>=1;}return z;}
#define int ll

const ll N=1e6+5;
ll fac[N],inv[N];
ll C(ll n,ll m){return (n>=m&&m>=0)?fac[n]*inv[m]%P*inv[n-m]%P:0;}
int n;char c[N];
int s1[N],s2[N];
int32_t main(){
	__file("bracket");
	cin.tie(nullptr)->sync_with_stdio(false);
	ll i;
	fac[0]=1;for(i=1;i<N;i++) fac[i]=fac[i-1]*i%P;
	inv[N-1]=qpow(fac[N-1]);for(i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%P;
	cin>>(c+1),n=strlen(c+1);
	for(i=1;i<=n;i++){
		s1[i]=s1[i-1]+(c[i]=='(');
		s2[i]=s2[i-1]+(c[i]=='?');
	}
	ll ans=0;
	for(i=1;i<n;i++){
		ll a=s1[i],b=n-s1[n]-s2[n]-(i-s1[i]-s2[i]),x=s2[i],y=s2[n]-x;
		(ans+=b*C(x+y,y+b-a)+y*C(x+y-1,y+b-a))%=P;
	}
	cout<<ans<<'\n';
	return 0;
}