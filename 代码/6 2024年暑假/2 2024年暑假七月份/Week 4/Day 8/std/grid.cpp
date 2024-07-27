#include<bits/stdc++.h>
using namespace std;

bool bo[500010];
struct Node{int l,r; vector<int> s1,s2;}t[2000010];
pair<int,int> a[500010];
int H,W,n,xl[500010],xr[500010],yl[500010],yr[500010];
long long ans;

int read()
{
	int p=0; char c=getchar();
	while (c>'9'||c<'0') c=getchar();
	while (c>='0'&&c<='9') p=p*10+c-48,c=getchar();
	return p;
}

void build(int i,int l,int r)
{
	t[i].l=l,t[i].r=r,t[i].s1.clear(),t[i].s2.clear();
	if (l==r) return;
	int mid=(l+r)>>1;
	build(i<<1,l,mid),build(i<<1|1,mid+1,r);
}

void add(int i,int l,int r,int v)
{
	t[i].s1.push_back(v);
	if (t[i].l==l&&t[i].r==r) {t[i].s2.push_back(v); return;}
	int mid=(t[i].l+t[i].r)>>1;
	if (r<=mid) add(i<<1,l,r,v); else
	if (l>mid) add(i<<1|1,l,r,v); else
	add(i<<1,l,mid,v),add(i<<1|1,mid+1,r,v);
}

int find(int i,int l,int r,int ql)
{
	while (!t[i].s2.empty()&&!bo[t[i].s2.back()]) t[i].s2.pop_back();
	if (!t[i].s2.empty()&&yr[t[i].s2.back()]>=ql) return t[i].s2.back();
	if (t[i].l==l&&t[i].r==r)
	{
		while (!t[i].s1.empty()&&!bo[t[i].s1.back()]) t[i].s1.pop_back();
		if (!t[i].s1.empty()&&yr[t[i].s1.back()]>=ql) return t[i].s1.back();
		return 0;
	}
	int mid=(t[i].l+t[i].r)>>1;
	if (r<=mid) return find(i<<1,l,r,ql);
	if (l>mid) return find(i<<1|1,l,r,ql);
	int ans=find(i<<1,l,mid,ql);
	return ans?ans:find(i<<1|1,mid+1,r,ql);
}

int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	H=read(),W=read(),n=read(),ans=0,build(1,1,H);
	for (int i=1; i<=n; i++) a[i].second=read(),a[i].first=read(),bo[i]=1;
	sort(a+1,a+1+n);
	for (int i=1; i<=n; i++) 
	{
		xl[i]=xr[i]=a[i].second,yl[i]=yr[i]=a[i].first;
		while (1)
		{
			int p=find(1,xl[i],xr[i],max(yl[i]-2,1));
			if (!p) p=find(1,max(xl[i]-2,1),min(xr[i]+2,H),yl[i]);
			if (!p) p=find(1,max(xl[i]-1,1),min(xr[i]+1,H),max(yl[i]-1,1));
			if (!p) 
			{
				add(1,xl[i],xr[i],i);
				ans+=1ll*(xr[i]-xl[i]+1)*(yr[i]-yl[i]+1);
				break;
			}
			ans-=1ll*(xr[p]-xl[p]+1)*(yr[p]-yl[p]+1),bo[p]=0;
			xl[i]=min(xl[i],xl[p]),xr[i]=max(xr[i],xr[p]);
			yl[i]=min(yl[i],yl[p]),yr[i]=max(yr[i],yr[p]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
