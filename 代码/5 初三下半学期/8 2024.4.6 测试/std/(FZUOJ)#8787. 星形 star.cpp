#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=998244353;
inline int addmod(int x)
{
	return x>=mod?x-mod:x;
}
inline int submod(int x)
{
	return x<0?x+mod:x;
}
struct edge
{
	int v,nxt;
}e[5000005];
int n,h[2000005],t,sz[2000005],ans;
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
void dfs(int u,int fa)
{
	sz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
	int mul=n-sz[u]+1,sum=n-sz[u],nw=0;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		mul=1ll*mul*(sz[v]+1)%mod;
		nw=(nw+1ll*sum*sz[v])%mod;
		sum=addmod(sum+sz[v]);
	}
	nw=submod(mul-nw);
	nw=submod(nw-n);
	ans=addmod(ans+nw);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
