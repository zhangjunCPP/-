#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N],b[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	int sum=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum+=min(abs(a[i]-a[j]),abs(b[i]-b[j]));
	cout<<sum;
}