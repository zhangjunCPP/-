#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int a[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("perfect.in","r",stdin);
	freopen("perfect.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n<=5000) {
		int ans=0;
		for(int l=1;l<=n;l++) {
			int Max=-1,Min=1e7;
			for(int r=l;r<=n;r++) {
				Max=max(Max,a[r]);
				Min=min(Min,a[r]);
				ans=max(ans,Max^Min);
			}
		}
		cout<<ans;
		return 0;
	}
	int ans=0;
	for(int l=1;l<=n-1;l++)ans=max(ans,a[l]^a[l+1]);
	cout<<ans;
}