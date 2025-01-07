#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)ans=max(ans,a[i]|a[j]|a[k]);
	cout<<ans;
}