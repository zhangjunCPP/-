#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
typedef long long ll;
const int MB=1<<20;
struct FastIO
{
	char ib[MB+100],*p,*q;
	char ob[MB+100],*r,stk[128];
	int tp;
	
	FastIO(){p=q=ib,r=ob,tp=0;}
	~FastIO(){fwrite(ob,1,r-ob,stdout);}
	
	char read_char()
	{
		if(p==q)
		{
			p=ib,q=ib+fread(ib,1,MB,stdin);
			if(p==q)return 0;
		}
		return *p++;
	//	return getchar();
	}
	template<typename T>
	void read_int(T& x)
	{
	//	scanf("%d",&x);
		char c=read_char(),l=0;
		for(x=0;!isdigit(c);c=read_char())l=c;
		for(;isdigit(c);c=read_char())x=x*10-'0'+c;
		if(l=='-')x=-x;
	}
	
	void write_char(char c)
	{
		if(r-ob==MB)r=ob,fwrite(ob,1,MB,stdout);
		*r++=c;
	}
	template<typename T>
	void write_int(T x)
	{
		if(x<0)write_char('-'),x=-x;
		do stk[++tp]=x%10+'0';
		while(x/=10);
		while(tp)write_char(stk[tp--]);
	//	printf("%lld\n",x);
	}
}IO;
int n,m;
ll sum[2000005],lazy[2000005],f[2000005];
inline int lowbit(int x)
{
	return x&-x;
}
void modify(int x,int v)
{
	if(!x) return;
	int nw=x,s=0;
	for(int i=x+lowbit(x);i<=n;i+=lowbit(i))
	{
		while(nw&&lowbit(nw)<lowbit(i))
		{
			s+=f[lowbit(nw)];
			lazy[nw]+=v;
			sum[nw]+=1ll*f[lowbit(nw)]*v;
			nw-=lowbit(nw);
		}
		sum[i]+=1ll*s*v;
	}
	while(nw)
	{
		lazy[nw]+=v;
		sum[nw]+=1ll*f[lowbit(nw)]*v;
		nw-=lowbit(nw);
	}
}
ll query(int x)
{
	if(!x) return 0;
	int nw=x,s=0;
	ll ans=0;
	for(int i=x+lowbit(x);i<=n;i+=lowbit(i))
	{
		while(nw&&lowbit(nw)<lowbit(i))
		{
			s+=f[lowbit(nw)];
			ans+=sum[nw];
			nw-=lowbit(nw);
		}
		s+=x-(i-lowbit(i));
		ans+=1ll*lazy[i]*s;
	}
	while(nw)
	{
		ans+=sum[nw];
		nw-=lowbit(nw);
	}
	return ans;
}
int main()
{
	f[1]=1;
	for(int i=1;i<=20;i++)
		f[1<<i]=f[1<<(i-1)]*2+(1<<(i-1));
	IO.read_int(n),IO.read_int(m);
	for(int i=1;i<=m;i++)
	{
		int op,l,r,v;
		IO.read_int(op),IO.read_int(l),IO.read_int(r);
		if(op==1)
		{
			IO.read_int(v);
			modify(r,v);
			modify(l-1,-v);
		}
		else
		{
			IO.write_int(query(r)-query(l-1));
			IO.write_char('\n');
		}
	}
	return 0;
}