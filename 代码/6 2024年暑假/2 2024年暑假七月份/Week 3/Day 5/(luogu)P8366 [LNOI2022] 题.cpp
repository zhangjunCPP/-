#include <bits/stdc++.h>
using namespace std;
const int N=20;
const int mod=1e9+7;
int dp[2][N][N][N][N][N][N];
void solve() {
	int n;
	cin>>n;
	string s;
	cin>>s;
	dp[0][0][0][0][0][0][0]=1;
	for(int i=1;i<=n*3;i++) {
		int tmp=i&1;
		int last=3*n-i+1;
		for(int a=0;2*a<=last&&a<=n&&a<=i;a++)
			for(int b=0;2*(a+b)<=last&&a+b<=n&&a+b<=i;b++)
				for(int c=0;2*(a+b+c)<=last&&a+b+c<=n&&a+b+c<=i;c++)
					for(int d=0;2*(a+b+c)+d<=last&&a+b+c+d<=n&&a+b+c+2*d<=i;d++)
						for(int e=0;2*(a+b+c)+d+e<=last&&a+b+c+d+e<=n&&a+b+c+2*d+2*e<=i;e++)
							for(int f=0;2*(a+b+c)+d+e+f<=last&&a+b+c+d+e+f<=n&&a+b+c+2*d+2*e+2*f<=i;f++)
								dp[tmp][a][b][c][d][e][f]=0;
		if(s[i-1]=='1'||s[i-1]=='0') {
			for(int a=0;2*a<=last&&a<=n&&a<=i;a++)
				for(int b=0;2*(a+b)<=last&&a+b<=n&&a+b<=i;b++)
					for(int c=0;2*(a+b+c)<=last&&a+b+c<=n&&a+b+c<=i;c++)
						for(int d=0;2*(a+b+c)+d<=last&&a+b+c+d<=n&&a+b+c+2*d<=i;d++)
							for(int e=0;2*(a+b+c)+d+e<=last&&a+b+c+d+e<=n&&a+b+c+2*d+2*e<=i;e++)
								for(int f=0;2*(a+b+c)+d+e+f<=last&&a+b+c+d+e+f<=n&&a+b+c+2*d+2*e+2*f<=i;f++){
									if(a)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+dp[tmp^1][a-1][b][c][d][e][f])%mod;
									if(b<n&&d)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(b+1)%mod*dp[tmp^1][a][b+1][c][d-1][e][f]%mod)%mod;
									if(f<n)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(f+1)%mod*dp[tmp^1][a][b][c][d][e][f+1]%mod)%mod;
								}
		}
		if(s[i-1]=='2'||s[i-1]=='0') {
			for(int a=0;2*a<=last&&a<=n&&a<=i;a++)
				for(int b=0;2*(a+b)<=last&&a+b<=n&&a+b<=i;b++)
					for(int c=0;2*(a+b+c)<=last&&a+b+c<=n&&a+b+c<=i;c++)
						for(int d=0;2*(a+b+c)+d<=last&&a+b+c+d<=n&&a+b+c+2*d<=i;d++)
							for(int e=0;2*(a+b+c)+d+e<=last&&a+b+c+d+e<=n&&a+b+c+2*d+2*e<=i;e++)
								for(int f=0;2*(a+b+c)+d+e+f<=last&&a+b+c+d+e+f<=n&&a+b+c+2*d+2*e+2*f<=i;f++){
									if(b)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+dp[tmp^1][a][b-1][c][d][e][f])%mod;
									if(c<n&&f)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(c+1)%mod*dp[tmp^1][a][b][c+1][d][e][f-1]%mod)%mod;
									if(e<n)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(e+1)%mod*dp[tmp^1][a][b][c][d][e+1][f]%mod)%mod;
								}

		}
		if(s[i-1]=='3'||s[i-1]=='0') {
			for(int a=0;2*a<=last&&a<=n;a++)
				for(int b=0;2*(a+b)<=last&&a+b<=n;b++)
					for(int c=0;2*(a+b+c)<=last&&a+b+c<=n;c++)
						for(int d=0;2*(a+b+c)+d<=last&&a+b+c+d<=n;d++)
							for(int e=0;2*(a+b+c)+d+e<=last&&a+b+c+d+e<=n;e++)
								for(int f=0;2*(a+b+c)+d+e+f<=last&&a+b+c+d+e+f<=n;f++) {
									if(c)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+dp[tmp^1][a][b][c-1][d][e][f])%mod;
									if(a<n&&e)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(a+1)%mod*dp[tmp^1][a+1][b][c][d][e-1][f]%mod)%mod;
									if(d<n)dp[tmp][a][b][c][d][e][f]=(dp[tmp][a][b][c][d][e][f]+1ll*(d+1)%mod*dp[tmp^1][a][b][c][d+1][e][f]%mod)%mod;
								}
		}
	}
	int ans=dp[(3*n)&1][0][0][0][0][0][0];
	for(int i=1;i<=n;i++)ans=1ll*ans*i%mod;
	cout<<ans%mod<<"\n";
	for(int a=0;a<=n;a++)
		for(int b=0;a+b<=n;b++)
			for(int c=0;a+b+c<=n;c++)
				for(int d=0;a+b+c+d<=n;d++)
					for(int e=0;a+b+c+d+e<=n;e++)
						for(int f=0;a+b+c+d+e+f<=n;f++)
							dp[0][a][b][c][d][e][f]=dp[1][a][b][c][d][e][f]=0;
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}