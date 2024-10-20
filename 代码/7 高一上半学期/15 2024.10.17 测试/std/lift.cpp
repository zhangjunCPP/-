#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t;
bool a[500005];
pair<int,pair<int,int>> p[500005];
int ans;
void add(int x)
{
	if(x>=m)
	{
		ans+=t*(1<<(x-m));
		return;
	}
	if(a[x])
	{
		a[x]=0;
		add(x+1);
	}
	else
	{
		a[x]=1;
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<m;i++)	a[i]=1;
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		p[i]={z,{x,y}};
	}
	sort(p+1,p+n+1);
	for(int i=n;i>=1;i--)
	{
		t=p[i].first;
		int x=p[i].second.first;
		int y=p[i].second.second;
		while(x)
		{
			add(__lg(x&-x)+y);
			x-=x&-x;
		}
	}
	cout<<ans<<endl;
	return 0;
}