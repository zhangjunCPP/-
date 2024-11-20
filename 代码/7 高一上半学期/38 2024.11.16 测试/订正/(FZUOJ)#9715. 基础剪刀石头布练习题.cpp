#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000+10,mod=998244353,lim=2000;
const int inv3=(mod+1)/3;
int a[N];
int dp[N][N*2][3];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	dp[0][0+lim][0]=dp[0][0+lim][1]=dp[0][0+lim][2]=1;
	for(int i=1;i<=n;i++){
		if(a[i]==-1)ans=ans*3%mod;
		for(int j=-n;j<=n;j++)
			for(int k=0;k<3;k++)
				if(dp[i-1][j+lim][k])
					for(int l=0;l<3;l++)
						if(a[i]==-1||l==a[i]){
							int val1,val2;
							if(l==(k+1)%3)val1=0,val2=max(1ll,j+1);
							else if(l==k)val1=j,val2=1;
							else val1=max(0ll,j),val2=j+1;
							ans=(ans+dp[i-1][j+lim][k]*val1)%mod;
							dp[i][val2-val1+lim][l]=(dp[i][val2-val1+lim][l]+dp[i-1][j+lim][k])%mod;
						}
	}
	for(int i=-n;i<=n;i++)for(int j=0;j<3;j++)ans=(ans+max(i,0ll)*dp[n][i+lim][j])%mod;
	cout<<ans*inv3%mod;
}