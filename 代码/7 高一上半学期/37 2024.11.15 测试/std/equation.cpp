#include<bits/stdc++.h>
#define fir first
#define sec second
#define all(x) begin(x),end(x)
using namespace std;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef __int128 int128;
typedef __uint128_t uint128;
typedef pair<int,int> pii;
template<typename type>
inline void chmin(type &x,const type &y)
{
	if(y<x)
		x=y;
}
template<typename type>
inline void chmax(type &x,const type &y)
{
	if(x<y)
		x=y;
}
constexpr int mod=998244353,inv2=(mod+1)/2;
inline void mod_add(int &x,const int &y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline int exgcd(int a,int b,int &x,int &y)
{
	x=1,y=0;
	int u=0,v=1,k;
	while(b)
	{
		k=a/b;
		tie(x,u)=pii(u,x-k*u);
		tie(y,v)=pii(v,y-k*v);
		tie(a,b)=pii(b,a-k*b);
	}
	return a;
}
inline int f(int m,int a,int b)
{
	static int x,y;
	int g=exgcd(a,m,x,y);
	if(b%g)
		return -1;
	int o=m/g;
	x=(ll)x*b/g%o;
	if(x<0)
		x+=o;
	return x;
}
void solve()
{
	ll n;
	int a,b;
	cin>>n>>a>>b;
	int ans=0;
	if(n>b)
		for(int i=0;i<a;++i)
		{
			ll x=f(a,i,-b);
			if(!~x)
				continue;
			ll l=b<i?0:(b-i)/a+1;
			ll r=n<i?-1:(n-i)/a;
			if(l>r)
				continue;
			ll u=((i*x+b)/a+l*x)%mod;
			ll v=((i*x+b)/a+r*x)%mod;
			mod_add(ans,(r-l+1)%mod*(u+v)%mod);
		}
	ans=(ll)ans*inv2%mod;
	for(int i=min(n,(ll)b);i;--i)
	{
		int x=f(i,a,b);
		if(~x)
			mod_add(ans,x);
	}
	cout<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}