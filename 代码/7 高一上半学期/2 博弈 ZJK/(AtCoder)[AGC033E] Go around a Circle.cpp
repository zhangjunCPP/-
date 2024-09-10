#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
int dp1[N],dp2[N];
int c[N],tot;
signed main() {
	int n,m;
	string s;
	cin>>n>>m>>s;
	for(int l=0,r=0;l<m;) {
		while(r+1<m&&s[r+1]==s[l])r++;
		c[++tot]=r-l+1;
		r++;l=r;
	}
	if(tot==1) {
		if(n==1){cout<<1;return 0;}
		if(n==2){cout<<3;return 0;}
		dp1[0]=1,dp1[1]=2;
		for(int i=2;i<=n;i++)dp1[i]=(dp1[i-1]+dp1[i-2])%mod;
		cout<<(dp1[n-1]+dp1[n-3])%mod;
		return 0;
	}
	if(n&1){cout<<0;return 0;}
	if(tot&1)tot--;
	int Min=c[1]+!(c[1]&1);
	for(int i=3;i<=tot;i+=2)if(c[i]&1)Min=min(Min,c[i]);
	n/=2,Min/=2;
	dp1[1]=dp2[1]=1;
	for(int i=2;i<=n;i++) {
		dp1[i]=(dp2[i-1]-(i-Min-2>=0?dp2[i-Min-2]:0)+mod)%mod;
		dp2[i]=dp2[i-1]+dp1[i];
	}
	int ans=0;
	for(int i=0;i<=min(n,Min);i++)ans=(ans+dp1[n-i]*(i+1)%mod)%mod;
	cout<<ans*2%mod;
}