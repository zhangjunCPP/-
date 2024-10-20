#include<bits/stdc++.h>
using namespace std;
int n,m;
int sqn;
struct que{
	int l,r,id;
}q[100005];
bool cmp(que a,que b)
{
	if(a.l/sqn!=b.l/sqn)	return a.l<b.l;
	if(a.l/sqn&1)	return a.r<b.r;
	return a.r>b.r;
}
int a[100005];
int b[100005];
priority_queue< pair<int,int> > l,r;
int nl,nr,mid;
unsigned int sl,sr,ans[100005];
int ll,rr;
void gm()
{
	while(!l.empty()&&b[l.top().second]!=-1)	l.pop();
	while(!r.empty()&&b[r.top().second]!=1)		r.pop();
	if(nl>nr+1)
	{
		int x=l.top().second;
		b[x]=1;
		nl--;
		sl-=a[x];
		l.pop();
		nr++;
		sr+=a[x];
		r.push({-a[x],x});
		mid=a[x];
	}
	else if(nl+1<nr)
	{
		int x=r.top().second;
		b[x]=-1;
		nr--;
		sr-=a[x];
		r.pop();
		nl++;
		sl+=a[x];
		l.push({a[x],x});
		mid=a[x];
	}
	else if(nl>=nr)
	{
		mid=l.top().first;
	}
	else
	{
		mid=-r.top().first;
	}
}
void add(int x)
{
	if(a[x]<=mid)
	{
		nl++;
		sl+=a[x];
		b[x]=-1;
		l.push({a[x],x});
	}
	else
	{
		nr++;
		sr+=a[x];
		b[x]=1;
		r.push({-a[x],x});
	}
	gm();
}
void del(int x)
{
	if(b[x]==-1)
	{
		nl--;
		sl-=a[x];
	}
	else
	{
		nr--;
		sr-=a[x];
	}
	b[x]=0;
	gm();
}
int main()
{
	scanf("%d%d",&n,&m);
	sqn=sqrt(n)*3/2;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	ll=q[1].l,rr=ll-1;
	for(int i=1;i<=m;i++)
	{
		while(rr<q[i].r)	add(++rr);
		while(ll>q[i].l)	add(--ll);
		while(rr>q[i].r)	del(rr--);
		while(ll<q[i].l)	del(ll++);
		if(nl>nr+1)	cerr<<i<<'l'<<'\n';
		if(nr>nl+1)	cerr<<i<<'r'<<'\n';
		if(-r.top().first<l.top().first)	cerr<<i<<'m'<<'\n';
		ans[q[i].id]=mid*(nl-nr)+sr-sl;
	}
	for(int i=1;i<=m;i++)	printf("%d\n",ans[i]);
	return 0;
}