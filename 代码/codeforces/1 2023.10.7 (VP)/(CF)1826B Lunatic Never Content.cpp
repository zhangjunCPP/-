#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int ans=0;
	for(int l=1,r=n;l<=r;l++,r--) ans=__gcd(ans,abs(a[l]-a[r]));
	cout<<ans<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}