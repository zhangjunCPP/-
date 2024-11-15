#include<bits/stdc++.h>
#define fir first
#define sec second
#define all(x) begin(x),end(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef double db;
typedef long double ldb;
typedef pair<int,int> pii;
template<typename type>
inline void chmax(type &x,const type &y)
{
	if(x<y)
		x=y;
}
template<typename type>
inline void chmin(type &x,const type &y)
{
	if(y<x)
		x=y;
}
constexpr int Max=1e6+10;
constexpr ll mod=998244353;
inline ll qpow(ll x,ll y=mod-2)
{
	ll ans=1;
	for(;y;(x*=x)%=mod,y>>=1)
		if(y&1)
			(ans*=x)%=mod;
	return ans;
}
ll fac[Max],inv_fac[Max];
void init(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i%mod;
	inv_fac[n]=qpow(fac[n]);
	for(int i=n;i;--i)
		inv_fac[i-1]=inv_fac[i]*i%mod;
}
void solve()
{
	int n,m;
	cin>>n>>m;
	int x,k=n;
	for(int i=1;i<=m;++i)
		cin>>x,chmin(k,x);
	if(!k)
		cout<<fac[n]*inv_fac[m]%mod<<"\n";
	else
		cout<<(m+1)*fac[k]%mod*fac[n]%mod*inv_fac[m+k]%mod<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	init(1'000'000);
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}