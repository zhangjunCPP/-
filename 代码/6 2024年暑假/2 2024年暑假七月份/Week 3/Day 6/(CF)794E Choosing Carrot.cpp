#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int ans[N];
int h[N],g[N];
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans[1]=max(ans[1],a[i]);
	for(int i=1;i<n;i++)h[min(i,n-i)]=max({h[min(i,n-i)],a[i],a[i+1]});
	for(int i=2;i<n;i++)g[min(i-1,n-i)]=max({g[min(i-1,n-i)],min(a[i-1],a[i]),min(a[i],a[i+1])});
	for(int i=n/2;i;i--) {
		ans[i*2]=max(ans[i*2+2],h[i]);
		ans[i*2+1]=max(ans[i*2+3],g[i]);
	}
	for(int i=n;i>=1;i--)cout<<ans[i]<<" ";
}