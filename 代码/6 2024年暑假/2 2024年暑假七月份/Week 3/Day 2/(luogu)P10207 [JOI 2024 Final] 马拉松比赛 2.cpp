#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,INF=1e18;
int a[N];
int cnt[N];
int pre[N],suf[N];
int dp[1005][1005][2][2];
signed main() {
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		cnt[a[i]]++;
	}
	cin>>q;
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	if(n>1000) {
		while(q--)puts("No");
		return 0;
	}
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+cnt[a[i]];
	for(int i=n;i>=1;i--)suf[i]=suf[i+1]+cnt[a[i]];
	dp[1][n][0][0]=dp[1][n][1][1]=0;
	for(int len=n;len>1;len--) {
		for(int l=1;l+len-1<=n;l++) {
			int r=l+len-1;
			for(int k=0;k<=1;k++) {
				int sum=pre[l-1]+suf[r+1]+1,suml=cnt[a[l]],sumr=cnt[a[r]];
				dp[l+1][r][0][k]=min({dp[l+1][r][0][k],dp[l][r][0][k]+(sum+suml)*(a[l+1]-a[l]),dp[l][r][1][k]+sum*(a[r]-a[l])+(sum+suml)*(a[l+1]-a[l])});
				dp[l+1][r][1][k]=min({dp[l+1][r][1][k],dp[l][r][0][k]+(sum+suml)*(a[r]-a[l]),dp[l][r][1][k]+sum*(a[r]-a[l])+(sum+suml)*(a[r]-a[l])});
				dp[l][r-1][0][k]=min({dp[l][r-1][0][k],dp[l][r][0][k]+sum*(a[r]-a[l])+(sum+sumr)*(a[r]-a[l]),dp[l][r][1][k]+(sum+sumr)*(a[r]-a[l])});
				dp[l][r-1][1][k]=min({dp[l][r-1][1][k],dp[l][r][0][k]+sum*(a[r]-a[l])+(sum+sumr)*(a[r]-a[r-1]),dp[l][r][1][k]+(sum+sumr)*(a[r]-a[r-1])});
			}
		}
	}
	while(q--) {
		int s,g,t;
		cin>>s>>g>>t;
		int sum=pre[n]+1;
		int pos=lower_bound(a+1,a+1+n,g)-a;
		int ans=INF;
		if(pos>1) ans=min({ans,abs(a[1]-s)+dp[pos-1][pos-1][0][0]+sum*abs(a[pos-1]-g),abs(a[n]-s)+dp[pos-1][pos-1][0][1]+sum*abs(a[pos-1]-g)});
		if(pos<=n) ans=min({ans,abs(a[1]-s)+dp[pos][pos][0][0]+sum*abs(a[pos]-g),abs(a[n]-s)+dp[pos][pos][0][1]+sum*abs(a[pos]-g)});
		if(ans+pre[n]<=t) puts("Yes");
		else puts("No");
	}
}