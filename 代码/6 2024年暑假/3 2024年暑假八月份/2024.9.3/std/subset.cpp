#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
#define N 1050
#define ll long long
int T,n,s[N][2],v[N];
int s1[27],id[N],st[N];
ll sa,sb,as;
struct sth{int a,b,id;};
bool operator <(sth a,sth b)
{
	ll tp=1ll*a.a*b.b-1ll*a.b*b.a;
	if(tp)return tp<0;
	else return a.id<b.id;
}
set<sth> fu;
bool check(int x,int y){return s[y][1]<s[x][1];}
bool cmp1(int x,int y){return s[x][0]<s[y][0];}
sth doit(int x,int y,int id){return (sth){s[x][0]-s[y][0],s[y][1]-s[x][1],id};}
void ins(int x)
{
	int vl=v[x];
	for(int j=25;j>=1;j--)
	if((vl>>j-1)&1)
	if(s1[j])vl^=s1[j];
	else
	{
		s1[j]=vl;id[x]=j;
		sa+=s[x][0];sb+=s[x][1];
		return;
	}
}
void solve()
{
	fu.clear();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&v[i],&s[i][0],&s[i][1]);
		st[i]=i;id[i]=0;
	}
	for(int i=0;i<=25;i++)s1[i]=0;
	sa=sb=0;
	sort(st+1,st+n+1,cmp1);
	for(int i=1;i<=n;i++)ins(st[i]);
	as=sa*sb;
	for(int i=1;i<n;i++)if(check(st[i],st[i+1]))fu.insert(doit(st[i],st[i+1],i));
	while(!fu.empty())
	{
		sth v1=*fu.begin();
		fu.erase(v1);
		int x=v1.id;
		if(x>1&&check(st[x-1],st[x]))fu.erase(doit(st[x-1],st[x],x-1));
		if(x+1<n&&check(st[x+1],st[x+2]))fu.erase(doit(st[x+1],st[x+2],x+1));
		if(id[st[x]])sa-=s[st[x]][0],sb-=s[st[x]][1],s1[id[st[x]]]=0,id[st[x]]=0;
		if(id[st[x+1]])sa-=s[st[x+1]][0],sb-=s[st[x+1]][1],s1[id[st[x+1]]]=0,id[st[x+1]]=0;
		swap(st[x],st[x+1]);
		ins(st[x]);ins(st[x+1]);
		as=min(as,sa*sb);
		if(x>1&&check(st[x-1],st[x]))fu.insert(doit(st[x-1],st[x],x-1));
		if(x+1<n&&check(st[x+1],st[x+2]))fu.insert(doit(st[x+1],st[x+2],x+1));
	}
	printf("%lld\n",as);
}
int main()
{
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	scanf("%d",&T);
	while(T--)solve();
}
