#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N];
bool cmp(const int&x,const int&y){return x>y;}
bool flag[N];

signed main() {
	freopen("contest.in","r",stdin);
	freopen("contest.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(int i=2;i<=n-5;i++)if(a[i]+a[i+1]<a[i+2]+a[i+3]+a[i+4]+a[i+5])flag[i]=true;
	int ans=-1,pos=-1;
	for(int i=n-6;i>=1;i--) {
		if(flag[i+1])pos=i+1;
		if(pos==-1)continue;
		if(a[i]<a[pos]+a[pos+1]&&a[pos]+a[pos+1]<a[pos+2]+a[pos+3]+a[pos+4]+a[pos+5]) {
			ans=max(ans,a[i]+a[pos]+a[pos+1]+a[pos+2]+a[pos+3]+a[pos+4]+a[pos+5]);
		}
	}
	cout<<ans;
}
/*
8
45 40 30 20 20 14 14 14
----
--    -- -- -- -- -- --
157
*/