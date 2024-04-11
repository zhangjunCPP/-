#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct pt
{
	int l,r,sz;
	pt(int l=0,int r=0,int sz=0):l(l),r(r),sz(sz){}
}p[2000005][2];
struct edge
{
	int v,nxt;
}e[5000005];
int T,n,a[2000005],st[2000005][2],tp,L[2000005],R[2000005],vis[2000005],pre[2000005];
int h[2000005],t,c[2000005];
char s[5000005]; 
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
pt merge(pt x,pt y)
{
	if(!x.sz) return y;
	if(!y.sz) return x;
	pt z;
	R[x.r]=y.l;
	L[y.l]=x.r;
//	printf("merge:x=%d,%d,y=%d,%d\n",x.l,x.r,y.l,y.r);
	z.l=x.l,z.r=y.r,z.sz=x.sz+y.sz;
	return z;
}
void dfs(int u,int fa,int w)
{
	c[u]=w;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(c[v]) continue;
		dfs(v,u,w^1);
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		t=0;
		scanf("%d",&n);
		n*=2;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=0;i<=n;i++)
			vis[i]=c[i]=h[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(vis[a[i]]) pre[i]=vis[a[i]];
			else vis[a[i]]=i,pre[i]=0;
		}
		tp=0;
		int fl=1;
		for(int i=1;i<=n;i++)
		{
			if(!pre[i])
			{
				st[++tp][0]=i;
				st[tp][1]=i;
				p[tp][0]=pt(a[i],a[i],1);
				p[tp][1]=pt();
				L[a[i]]=R[a[i]]=0;
				continue;
			}
			int u=pre[i];
			pt q;
			while(tp&&st[tp][0]>u)
			{
				if(p[tp][0].sz&&p[tp][1].sz)
				{
					fl=0;
					break;
				}
				if(p[tp][1].sz) swap(p[tp][1],p[tp][0]);
				if(p[tp][0].sz)
				{
					add(p[tp][0].l,a[u]);
					add(a[u],p[tp][0].l);
					q=merge(p[tp][0],q);
				}
				tp--;
			}
		/*	printf("i=%d,u=%d,tp=%d,st=%d,%d\n",i,u,tp,st[tp][0],st[tp][1]);
			for(int j=1;j<=tp;j++)
				printf("j=%d,st=%d,%d,p=%d,%d,%d:%d,%d,%d\n",
				j,st[j][0],st[j][1],p[j][0].l,p[j][0].r,p[j][0].sz,p[j][1].l,p[j][1].r,p[j][1].sz);
			for(int j=1;j<=n;j++)
				printf("j=%d,L=%d,R=%d\n",j,L[j],R[j]); */
			st[tp][1]=i;
			if(p[tp][1].sz&&a[u]==p[tp][1].r) swap(p[tp][1],p[tp][0]);
			if(p[tp][0].sz&&a[u]==p[tp][0].r)
			{
				p[tp][1]=merge(p[tp][1],q);
				p[tp][0].sz--;
				p[tp][0].r=L[p[tp][0].r];
			}
			else fl=0;
			if(!fl) break;
		}
		if(!fl)
		{
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n/2;i++)
			if(!c[i])
				dfs(i,0,2);
		s[n+1]=0;
		for(int i=1;i<=n;i++)
			s[i]=c[a[i]]-1+'0';
		printf("%s\n",s+1); 
	}
	return 0;
}
