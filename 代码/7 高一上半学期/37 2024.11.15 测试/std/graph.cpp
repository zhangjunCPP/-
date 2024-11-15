#include<bits/stdc++.h>
#define popcnt(x) __builtin_popcount(x)
using namespace std;
typedef long long ll;
typedef double db;
constexpr int Max=20,Size=1<<17;
constexpr ll mod=998244353;
int cnt[Size],e[Max],n,m,lim;
ll f[Size][3],inv[Max];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>lim;
	for(int i=1,u,v;i<=m;++i)
	{
		cin>>u>>v,--u,--v;
		e[u]|=1<<v,e[v]|=1<<u;
	}
	for(int S=1;S<1<<n;++S)
		cnt[S]=cnt[S&(S-1)]+popcnt(e[__lg(S&-S)]&S);
	inv[1]=1;
	for(int i=2;i<=n+1;++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	auto ask=[&](int S,int T)->int
	{
		return cnt[S|T]-cnt[S]-cnt[T];
	};
	for(int S=1;S<1<<n;++S)
	{
		int siz=popcnt(S);
		if(siz==1)
		{
			f[S][0]=1;
			continue;
		}
		int r=min(cnt[S]-siz+1,lim);
		if(r<0)
			continue;
		int O=S&(S-1);
		for(int T=O;T;T=(T-1)&O)
		{
			int w=ask(S^T,T);
			ll x=f[T][0]*w%mod;
			(f[S][0]+=x*f[S^T][0])%=mod;
			if(r)
			{
				ll y=f[T][1]*w%mod;
				(f[S][1]+=x*f[S^T][1]+y*f[S^T][0])%=mod;
				if(r>1)
				{
					ll z=f[T][2]*w%mod;
					(f[S][2]+=x*f[S^T][2]+y*f[S^T][1]+z*f[S^T][0])%=mod;
				}
			}
		}
		for(int i=0;i<=r;++i)
		{
			if(i)
				(f[S][i]+=f[S][i-1]*(cnt[S]-(siz+i-2)))%=mod;
			(f[S][i]*=inv[siz-1+i])%=mod;
		}
	}
	for(int i=0;i<=lim;++i)
		cout<<f[(1<<n)-1][i]<<"\n";
	// cout<<"times : "<<(db)clock()/CLOCKS_PER_SEC<<"\n";
	return 0;
}