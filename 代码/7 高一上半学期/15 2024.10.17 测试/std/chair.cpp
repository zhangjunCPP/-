#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t;
int q;
int a[500005];
int ta[500005],tt[500005];
int cheng=1,jia;
int ans[500005];
int gd(int x,int y)
{
	if(x%y==0)	return y;
	return gd(y,x%y);
}
int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	int d=exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-(a/b)*y;
	return d;
}
int ny(int x)
{
	int a,b;
	exgcd(x,m,a,b);
	return (a%m+m)%m;
}
signed main()
{
	scanf("%lld",&n);
	m=n;
	t=1;
	for(int i=1;i<n;i++)	a[i]=i;
	a[0]=n;
	scanf("%lld",&q);
	for(int i=0;i<n;i++)	tt[i]=n+1000;
	//cout<<n<<' '<<q<<'\n';
	while(q--)
	{
		int c;
		int x;
		scanf("\n%lld%lld",&c,&x);
			//cerr<<c<<' '<<x<<'\n';
		if(c==2)
		{
			jia+=x;
			jia%=n;
		}
		else if(c==3)
		{
			int cd=gd(m,x);
			if(cd==1)
			{
				cheng*=x;
				jia*=x;
				cheng%=n;
				jia%=n;
			}
			else
			{
				int tj=jia*x%n;
				for(int i=0;i<n;i+=t)
				{
					int to=(i*cheng+jia)%n;
					int kt=(to*x%n-to+n)%n+1;
					to=(to*x%n-tj+n)%n;
					if(tt[to]==0||kt<tt[to])
					{
						ta[to]=a[i];
						tt[to]=kt;
					}
				}
				cheng=1;
				jia=tj;
				t*=cd;
				m/=cd;
				for(int i=0;i<n;i+=t)
				{
					a[i]=ta[i];
					tt[i]=n+1000;
				}
			}
		}
		else
		{
			x=((x+n-jia)%n+n)%n;
			if(x%t==0)
			{
				ans[a[x*ny(cheng)%n]]++;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
