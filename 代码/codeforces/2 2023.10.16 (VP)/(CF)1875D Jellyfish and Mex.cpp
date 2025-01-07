#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int cnt[N];
int dp[N];
void solve(){
	int n;
	cin>>n;
	memset(cnt,0,sizeof(cnt));
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		if(a[i]<=n) cnt[a[i]]++;
	}
	int mex=0;
	while(cnt[mex]) mex++;
	dp[0]=0;
	for(int i=0;i<=mex;i++) {
		for(int j=0;j<i;j++) {
			dp[i]=min(dp[i],dp[j]+(cnt[j]-1)*i+j);
		}
	}
	cout<<dp[mex]<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}