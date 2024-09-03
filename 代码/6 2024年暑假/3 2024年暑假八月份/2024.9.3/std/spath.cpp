#include<cstdio>
using namespace std;
#define N 105000
#define mod 998244353
int T,a,b,c,d,fr[N],ifr[N],fg1,fg2;
struct sth{int a,b;};
int pw(int a,int b){int as=1;while(b){if(b&1)as=1ll*as*a%mod;a=1ll*a*a%mod;b>>=1;}return as;}
sth operator +(sth a,sth b){if(a.a<b.a)return a;if(a.a>b.a)return b;a.b=(a.b+b.b)%mod;return a;}
sth solve(int s,int t)
{
	int v1=b,v2=c,c1=0,tp21=1;
	if(s)v1--;else v2--;
	if(t)v1--;else v2--;
	if((s^a^1)&1)
	c1++,tp21*=fg1+1;
	if((t^d^1)&1)
	c1++,tp21*=fg2+1;
	if(v1<0||v2<0)return (sth){1000000000,0};
	if(v1<=v2&&v1+1<=c)
	{
		int tp=v1+1,tp2=c;
		int d1=tp2-tp+v1,d2=v1;
		int as1=1ll*tp21*fr[d1]*ifr[d2]%mod*ifr[d1-d2]%mod;
		as1=1ll*as1*pw(2,tp2-tp)%mod;
		c1+=2*(b+c-1)+(tp2-tp)+1;
		return (sth){c1,as1};
	}
	else
	{
		int tp=v2+1,tp2=b;
		int d1=tp2-tp+v2,d2=v2;
		int as1=1ll*tp21*fr[d1]*ifr[d2]%mod*ifr[d1-d2]%mod;
		as1=1ll*as1*pw(2,tp2-tp)%mod;
		c1+=2*(b+c-1)+(tp2-tp)+1;
		return (sth){c1,as1};
	}
}
int main()
{
	freopen("spath.in","r",stdin);
	freopen("spath.out","w",stdout); 
	fr[0]=ifr[0]=1;for(int i=1;i<=102000;i++)fr[i]=1ll*fr[i-1]*i%mod,ifr[i]=pw(fr[i],mod-2);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&b,&c,&a,&d);a^=1;d^=1;
		if(b==0&&c==0)
		{
			int as=(a-d+4)%4;
			if(as==3)as=1;printf("%d %d\n",as,as==2?2:1);continue;
		}
		if(b==0&&c==1)
		{
			int as=1,ct=1;
			if(a==0||a==2)as++;
			if(a==3)ct*=2,as+=2;
			if(d==0||d==2)as++;
			if(d==1)ct*=2,as+=2;
			printf("%d %d\n",as,ct);
			continue;
		}
		if(b==1&&c==0)
		{
			int as=1,ct=1;
			if(a==1||a==3)as++;
			if(a==2)ct*=2,as+=2;
			if(d==1||d==3)as++;
			if(d==0)ct*=2,as+=2;
			printf("%d %d\n",as,ct);
			continue;
		}
		int c1=0;fg1=fg2=0;
		if(a==3)a=0,c1++,fg1=1;
		if(a==2)a=1,c1++,fg1=1;
		if(d==0)d=3,c1++,fg2=1;
		if(d==1)d=2,c1++,fg2=1;
		sth as=solve(0,0)+solve(0,1)+solve(1,0)+solve(1,1);
		printf("%d %d\n",as.a+c1,as.b);
	}
}
