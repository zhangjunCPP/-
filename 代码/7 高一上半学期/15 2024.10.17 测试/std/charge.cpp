#include<bits/stdc++.h>
using namespace std;
struct E{
	int to,w,ww;
}a[1000005];
vector<int> to[6000];
const int inf=1e9;
int n,m,k,S,T,cnt=1;
long long an,ans;
void link(int s,int t,int w)
{
	a[++cnt]={t,w,0};
	to[s].push_back(cnt);
	a[++cnt]={s,w,0};
	to[t].push_back(cnt);
	a[++cnt]={t,inf,1};
	to[s].push_back(cnt);
	a[++cnt]={s,0,-1};
	to[t].push_back(cnt);
	a[++cnt]={s,inf,1};
	to[t].push_back(cnt);
	a[++cnt]={t,0,-1};
	to[s].push_back(cnt);
}
long long dis[6000],h[6000];
bool b[6000];
int dl[40000],head,tail;
bool bfs()
{
	for(int i=1;i<=T;i++)
		dis[i]=inf;
	head=tail=2000;
	dis[S]=0;
	dl[++tail]=S;
	while(head<tail)
	{
		int nx=dl[++head];
		if(b[nx])	continue;
		b[nx]=1;
		for(int i:to[nx])
		{
			if(a[i].w==0)	continue;
			int v=a[i].to;
			int w=a[i].ww+h[nx]-h[v];
			if(dis[v]<=dis[nx]+a[i].ww+h[nx]-h[v])	continue;
			dis[v]=dis[nx]+a[i].ww+h[nx]-h[v];
			if(w)	dl[++tail]=v;
			else	dl[head--]=v;
		}
	}
	for(int i=1;i<=T;i++)	dis[i]+=h[i],b[i]=0;
	for(int i=1;i<=T;i++)
		h[i]=dis[i];
	return 1;
}
int dinic(int nx=S,int w=inf)
{
	if(nx==T)
		return w;
	if(dis[nx]>dis[T])	return 0;
	b[nx]=1;
	int used=0;
	for(int &i:to[nx])
	{
		int v=a[i].to;
		if(b[v])	continue;
		if(a[i].w==0)	continue;
		if(dis[v]!=dis[nx]+a[i].ww)	continue;
		int tmp=dinic(v,min(w,a[i].w));
		used+=tmp;
		a[i].w-=tmp;
		a[i^1].w+=tmp;
		w-=tmp;
		ans+=a[i].ww*tmp;
		if(!w)	break;
	}
	if(!used)	dis[nx]=inf;
	b[nx]=0;
	return used;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=n*m+1,T=n*m+2;
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<m;j++)
		{
			int x;
			scanf("%d",&x);
			if(i==0)		link(j,T,x);
			else if(i==n-1)	link((i-1)*m+j,S,x);
			else			link((i-1)*m+j,i*m+j,x);
		}
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<m;j++)
		{
			int x;
			scanf("%d",&x);
			if(j!=0&&j!=m-1)
				link(i*m+j,i*m+j+1,x);
		}
	}
	scanf("%d",&k);
	while(bfs())
	{
//		cout<<'!'<<'\n';
		an+=dinic();
		if(!dis[T])
			an=0;
//		cout<<an<<' '<<ans<<' '<<dis[T]<<'\n';
		if(an>=k)
		{
			ans-=dis[T]*(an-k);
			break;
		}
	}
	cout<<ans<<'\n';
	return 0;
}