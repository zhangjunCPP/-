#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=998244353;
inline int addmod(int x)
{
	return x>=mod?x-mod:x;
}
inline int submod(int x)
{
	return x<0?x+mod:x;
}
int fpow(int x,int y,int m)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=1ll*ans*x%m;
		x=1ll*x*x%m;
		y/=2;
	}
	return ans;
}
struct pt
{
	ll t,x;
	bool operator<(const pt p) const
	{
		return t<p.t;
	}
}a[1000005];
int t,n,m,k,fr[2000005],infr[2000005],inv[2000005],pn=2e6;
ll pw[105];
const int mod2=1999997;
struct edge
{
	ll v;
	int w,las,nxt;
};
struct qwq
{
	edge e[2000005];
	int h[2000005],b[2000005],bt,t;
	void ins(ll x,int id,int &lans,int &ans)
	{
		ans=0,lans=-1;
		int u=x%mod2;
		for(int i=h[u];i;i=e[i].nxt)
			if(e[i].v==x)
			{
				lans=e[i].las,ans=e[i].w;
				e[i].las=id;
				e[i].w++;
				return;
			}
		e[++t].v=x;
		e[t].nxt=h[u];
		if(!h[u]) b[++bt]=u;
		h[u]=t;
		e[t].w=1,e[t].las=id;
	}
	void getcl()
	{
		t=0;
		for(int i=1;i<=bt;i++)
			h[b[i]]=0;
		bt=0;
	}
}T[2];
int solve()
{
	int tans=fpow(fr[k],1ll*n*fpow(k,n-1,mod-1)%(mod-1),mod);
	for(int i=1;i<=n;i++)
	{
		for(int l=1,r;l<=m;l=r+1)
		{
			r=l;
			while(r<m&&a[r+1].t/pw[n-i+1]==a[l].t/pw[n-i+1]) r++;
			T[0].getcl();
			T[1].getcl();
			for(int j=l;j<=r;j++)
			{
				int lans,ans;
				ll u=a[j].x/pw[i];
				int v=a[j].t/pw[n-i]%k;
				T[0].ins(u,v,lans,ans);
				if(lans==v) return 0;
				tans=1ll*tans*inv[k-ans]%mod;
				T[1].ins(a[j].x/pw[i-1],v,lans,ans);
				if(ans) return 0;
			}
		}
	}
	return tans;
}
int main()
{
	fr[0]=infr[0]=1;
	for(int i=1;i<=pn;i++)
		fr[i]=1ll*fr[i-1]*i%mod;
	infr[pn]=fpow(fr[pn],mod-2,mod);
	for(int i=pn-1;i>0;i--)
		infr[i]=1ll*infr[i+1]*(i+1)%mod;
	for(int i=1;i<=pn;i++)
		inv[i]=1ll*infr[i]*fr[i-1]%mod;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&k,&n,&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%lld%lld",&a[i].t,&a[i].x);
			a[i].t--,a[i].x--;
		}
		sort(a+1,a+m+1);
		pw[0]=1;
		for(int i=1;i<=n;i++)
			pw[i]=1ll*pw[i-1]*k;
		printf("%d\n",solve());
	}
	return 0;
}
