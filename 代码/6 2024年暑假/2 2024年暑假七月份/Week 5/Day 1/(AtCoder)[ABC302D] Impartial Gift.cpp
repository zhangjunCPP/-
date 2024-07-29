#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
vector<int> a,b;
signed main(){
	int n,m,d;
	cin>>n>>m>>d;
	for(int i=1;i<=n;i++){int x;cin>>x;a.push_back(x);}
	for(int i=1;i<=m;i++){int x;cin>>x;b.push_back(x);}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int ans=-1;
	for(int i=0;i<n;i++) {
		auto l=upper_bound(b.begin(), b.end(),a[i]+d);
		--l;
		if(l!=b.end())if(*l<=a[i]+d&&*l>=a[i]-d)ans=max(ans,*l+a[i]);
	}
	cout<<ans;
}