#include<cstdio>
#define MAXN 100001
using namespace std;

typedef long long ll;

int deg[MAXN];
ll ans=0;
int n,m;

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		++deg[u],++deg[v];
	}
	for(int i=1;i<=n;i++)
		ans+=(1ll*deg[i]*(n-1-deg[i]));
	printf("%lld",1ll*n*(n-1)*(n-2)/6-(ans>>1));
	return(0);
}