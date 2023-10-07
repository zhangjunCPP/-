#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int l[N],r[N];
void solve(){
	int n;
	cin>>n;
	for(int i=0;i<=n+1;i++) l[i]=r[i]=-0x3f3f3f3f;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) l[i]=max(l[i-1],a[i]+i);
	for(int i=n;i>=1;i--) r[i]=max(r[i+1],a[i]-i);
	int ans=0;
 	for(int i=2;i<=n-1;i++) ans=max(ans,a[i]+l[i-1]+r[i+1]);
	cout<<ans<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}
