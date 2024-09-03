#include<cstdio>
#include<queue>
using namespace std;
#define N 3101
int T,n,m,dis[N],head[N],cnt,is[N],tp[N];
char s[N];
struct edge{int t,next,v;}ed[N*3];
void adde(int f,int t,int v){ed[++cnt]=(edge){t,head[f],v};head[f]=cnt;}
bool check()
{
	for(int i=0;i<m*3/2;i++)head[i]=0,is[i]=0,dis[i]=1e9;cnt=0;
	for(int i=0;i<m;i++)adde(i,(i&(m/2-1))+m,0),adde((i&(m/2-1))+m,i,0);
	for(int i=0;i<m;i++)
	{
		int ls=m+(i>>1),t1=i&1,lb,rb;
		if(tp[i]==0)lb=rb=0;else if(tp[i]==1)lb=rb=1;else lb=0,rb=1;
		if(t1)lb--,rb--;
		adde(ls,i,rb),adde(i,ls,-lb);
	}
	queue<int> qu;
	qu.push(0);dis[0]=0;is[0]=1;
	while(!qu.empty())
	{
		int u=qu.front();qu.pop();is[u]=0;
		for(int i=head[u];i;i=ed[i].next)
		if(dis[ed[i].t]>dis[u]+ed[i].v)
		{
			dis[ed[i].t]=dis[u]+ed[i].v;
			if(!is[ed[i].t])
			{
				qu.push(ed[i].t);is[ed[i].t]=1;
				if(dis[0]<0)return 0;
			}
		}
	}
	return 1;
}
void solve()
{
	scanf("%d%s",&n,s);m=1<<(2*n+1);
	for(int i=m-1;i>=0;i--)if(s[i]=='1')
	{
		for(int j=i;j<m;j++)s[j]^=1;
		break;
	}
	for(int i=m-1;i>=0;i--)if(s[i]=='0')
	{
		for(int j=0;j<m;j++)tp[j]=j<=i?s[j]-'0':-1;
		tp[i]^=1;
		if(check())
		{
			for(int j=i+1;j<m;j++)
			{
				tp[j]=0;
				if(!check())tp[j]=1;
			}
			for(int j=0;j<m;j++)printf("%d",tp[j]);
			printf("\n");
			return;
		}
	}
	printf("-1\n");
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)solve();
}
