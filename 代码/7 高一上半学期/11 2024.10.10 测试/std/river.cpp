#include <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while (T--) {
		int n,L,R;
		scanf("%d%d%d",&n,&L,&R);
		int t=(n-R)/(R-L)+((n-R)%(R-L)!=0);
		long long sum=0,s=1LL*t*L;
		for (int i=1;i<=n;i++) {
			int x;
			scanf("%d",&x);
			x--;
			sum+=min(x/2,t);
		}
		if (sum<s) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}