#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int main() {
	freopen("minsub.in", "r",stdin);
	freopen("minsub.out", "w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=a[1],r=a[1];
	int ans=0;
	for(int i=2;i<=n;i++) {
		if(a[i]>=l) {
			int tmp=l;
			ans++;
			l=max(0,a[i]-r);
			r=a[i]-tmp;
		}
		else l=0,r=a[i];
	}
	if(!l)ans++;
	cout<<ans;
}