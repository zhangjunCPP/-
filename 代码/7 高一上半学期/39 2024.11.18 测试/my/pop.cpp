#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n;
int a[N],b[N];
int val1[N],cnt1;
int val2[N],cnt2;
int val3[N],cnt3;
int val4[N],cnt4;
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	int Max,Min;
	if(n&1)Max=(n+1)/2+1,Min=n/2;
	else Max=n/2+1,Min=n/2;
	for(int i=1;i<=n;i++){
		if(a[i]>=Max)val1[++cnt1]=i;
		if(a[i]<=Min)val2[++cnt2]=i;
		if(b[i]<=Min)val3[++cnt3]=i;
		if(b[i]>=Max)val4[++cnt4]=i;
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=cnt1;i++){
		ans1+=abs(val1[i]-val3[i]);
		ans2+=abs(val2[i]-val4[i]);
	}
	cout<<min(ans1,ans2);
}