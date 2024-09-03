#include<cstdio>
using namespace std;
#define N 100500
#define mod 998244353
int T,n,v[N],tr[N];
void add(int x,int k){for(int i=x;i<=n;i+=i&-i)tr[i]=(tr[i]+k)%mod;}
int que(int x){int as=0;for(int i=x;i;i-=i&-i)as=(as+tr[i])%mod;return as;}
int rd(){char s=getchar();int v=0;while(s<'0'||s>'9')s=getchar();while(s>='0'&&s<='9')v=v*10+s-'0',s=getchar();return v;}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout); 
	T=rd();
	while(T--)
	{
		n=rd();
		for(int i=1;i<=n;i++)v[i]=rd();
		for(int i=1;i<=n;i++)tr[i]=0;
		for(int i=1;i<=n*2;i++)
		{
			int vl=v[i<=n?n-i+1:i-n];
			add(vl,que(vl-1)+1);
		}
		printf("%d\n",1ll*que(n)*(mod+1)/2%mod);
	}
}
