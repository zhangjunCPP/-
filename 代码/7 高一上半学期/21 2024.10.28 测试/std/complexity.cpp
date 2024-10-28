#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int t=a%__gcd(b,d);
		int mod=__gcd(b,d);
		int na=b/mod*mod+t;
		if(b>d||na-mod>c||a<b)
			cout<<"No\n";
		else
			cout<<"Yes\n";
	}
}