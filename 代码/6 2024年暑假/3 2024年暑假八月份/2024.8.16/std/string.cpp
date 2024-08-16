#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=1e6+5; 

int a[maxn], b[maxn], dp[maxn][3];

void solve() {
	string s,t;
	cin>>s>>t;
	int n=s.size();
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0', b[i]=t[i-1]-'0';
	dp[1][0]=1+b[1], dp[1][1]=1+(b[1]^1), dp[1][2]=(a[1]^b[1]);
	for(int i=2;i<=n;i++) {
		dp[i][0]=min(dp[i-1][0]+(b[i]&&b[i-1]==0),min(dp[i-1][1]+1+(b[i]&&b[i-1]==1),dp[i-1][2]+1+(b[i]&&a[i-1]==b[i-1])));
		dp[i][1]=min(dp[i-1][0]+1+((b[i]^1)&&b[i-1]==0),min(dp[i-1][1]+((b[i]^1)&&b[i-1]==1),dp[i-1][2]+1+((b[i]^1)&&a[i-1]==b[i-1])));
		dp[i][2]=min(dp[i-1][0]+((b[i]^a[i])&&b[i-1]==0),min(dp[i-1][1]+((b[i]^a[i])&&b[i-1]==1),dp[i-1][2]+((b[i]^a[i])&&a[i-1]==b[i-1])));
	}
	cout<<min(dp[n][0],min(dp[n][1],dp[n][2]))<<'\n';
	return ;
}

int main() {
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll t; cin>>t;
	while(t--) solve();
	return 0;
}