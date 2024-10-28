#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int u,v,c,t,id;
}a[300005];
bool cmp(int x,int y)
{
	return a[x].c<a[y].c;
}
vector<int> v[100005];
vector<int> g[2000005],e[2000005];
int n,m;
int tot;
int cnt;
int belong[2000005];
stack<int> z;
int dfn[2000005],low[2000005],c;
bool f[2000005];
void tarjan(int pos)
{
	low[pos]=dfn[pos]=++c;
	z.push(pos);
	f[pos]=1;
	for(int x:e[pos])
	{
		if(!dfn[x])
		{
			tarjan(x);
			low[pos]=min(low[pos],low[x]);
		}
		else if(f[x])
			low[pos]=min(low[pos],low[x]);
	}
	if(dfn[pos]==low[pos])
	{
		cnt++;
		while(!z.empty()&&z.top()!=pos)
		{
			f[z.top()]=0;
			belong[z.top()]=cnt;
			z.pop();
		}
		z.pop();
		belong[pos]=cnt;
		f[pos]=0;
	}
}
bool check(int k)
{
	for(int i=1;i<=tot;i++)
		e[i]=g[i];
	for(int i=1;i<=m;i++)
		if(a[2*i-1].t>k)
			e[2*i].push_back(2*i-1);
	for(int i=1;i<=tot;i++)
		dfn[i]=f[i]=belong[i]=low[i]=0;
	cnt=c=0;
	for(int i=1;i<=2*m;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=m;i++)
		if(belong[2*i-1]==belong[2*i])
			return 0;
	return 1;
}
void print(int k)
{
	for(int i=1;i<=tot;i++)
		e[i]=g[i];
	for(int i=1;i<=m;i++)
		if(a[2*i-1].t>k)
			e[2*i].push_back(2*i-1);
	for(int i=1;i<=tot;i++)
		dfn[i]=f[i]=belong[i]=low[i]=0;
	cnt=c=0;
	for(int i=1;i<=2*m;i++)
		if(!dfn[i])
			tarjan(i);
	int ans=0;
	for(int i=1;i<=m;i++)
		if(belong[2*i-1]>belong[2*i])
			ans++;
	cout<<k<<"\n";
	if(ans)
	{
		cout<<1<<"\n"<<ans<<"\n";
		for(int i=1;i<=m;i++)
			if(belong[2*i-1]>belong[2*i])
				cout<<a[2*i-1].id<<" ";
	}
	else
		cout<<0<<"\n";
}
void test()
{
	for(int i=0;i<=1000000;i++)
		e[i].clear(),g[i].clear();
	cin>>n>>m;
	for(int i=0;i<=n;i++)
		v[i].clear();
	for(int i=1;i<=m;i++)
	{
		int u,v,c,t;
		cin>>u>>v>>t>>c;
		a[2*i-1]={u,v,c,t,i};
		::v[u].push_back(2*i-1);
		a[2*i]={v,u,c,t,i};
		::v[v].push_back(2*i);
	}
	tot=2*m;
	for(int i=1;i<=n;i++)
	{
		int fir=tot,sz=v[i].size();
		sort(v[i].begin(),v[i].end(),cmp);
		for(int j=0;j+1<v[i].size();j++)
		{
			g[tot+j+1].push_back(tot+j+2);
			g[tot+v[i].size()+j+2].push_back(tot+v[i].size()+j+1);
		}
		tot+=2*v[i].size();
		for(int j=0;j+1<v[i].size();j++)
		{
			if(a[v[i][j]].c!=a[v[i][j+1]].c)
				continue;
			g[tot+j+1].push_back(tot+j+2);
			g[tot+v[i].size()+j+2].push_back(tot+v[i].size()+j+1);
		}
		tot+=2*v[i].size();
		for(int j=0;j<v[i].size();j++)
		{
			if(j+2<=v[i].size())
				g[2*a[v[i][j]].id].push_back(fir+j+2);
			if(j>=1)
				g[2*a[v[i][j]].id].push_back(fir+sz+j);
			g[fir+j+1].push_back(2*a[v[i][j]].id-1);
			g[fir+sz+j+1].push_back(2*a[v[i][j]].id-1);
		}
		fir+=2*sz;
		 for(int j=0;j<v[i].size();j++)
		{
			if(j+2<=v[i].size()&&a[v[i][j]].c==a[v[i][j+1]].c)
				g[2*a[v[i][j]].id-1].push_back(fir+j+2);
			if(j>=1&&a[v[i][j]].c==a[v[i][j-1]].c)
				g[2*a[v[i][j]].id-1].push_back(fir+sz+j);
			g[fir+j+1].push_back(2*a[v[i][j]].id);
			g[fir+sz+j+1].push_back(2*a[v[i][j]].id);
		}
		fir+=2*sz;
	}
	int l=0,r=1e3,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	if(l==1e3+1)
	{
		cout<<"-1\n";
		return;
	}
	print(l);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test();
}