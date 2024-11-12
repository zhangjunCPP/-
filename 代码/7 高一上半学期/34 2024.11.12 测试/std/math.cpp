#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		int p1=floor(sqrt(n+0.5)),p2=floor(sqrt(m+0.5));
		long long ans=0;
		for(int x=1;x<=p1;x++)
			for(int y=1;y<=p2;y++)
				if(__gcd(x,y)==1)
				{
					int k=x+y;
					ans+=min(n/x,m/y)/k;
				}
		printf("%lld\n",ans);
	}
}