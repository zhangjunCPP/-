#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int fa[N],siz[N]; 
int dp[N];
int n;
int check(int mid) {
	for(int i=1;i<=n;i++) dp[i]=0;
	for(int i=n;i>=1;i--) dp[i]=max(dp[i]-mid,0ll),dp[fa[i]]+=dp[i]+1;
	return dp[1];
}
int ans[N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) siz[i]=1,ans[i]=0;
	for(int i=2;i<=n;i++) cin>>fa[i];
	for(int i=n;i>=2;i--) siz[fa[i]]+=siz[i];
	int l=0,r=n;
	while(l<r) {
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	check(l-1);
	ans[1]=(dp[1]==1);
	for(int i=2;i<=n;i++) if(ans[fa[i]]&&dp[i]) ans[i]=1;
	for(int i=1;i<=n;i++) {
		if(siz[i]-1>l||(siz[i]-1==l&&ans[i])) cout<<"1";
		else cout<<"0";
	}
	cout<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
