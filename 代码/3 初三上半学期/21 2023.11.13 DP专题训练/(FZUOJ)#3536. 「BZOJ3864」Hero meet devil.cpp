#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e5+10;
int popc(int x) {return __builtin_popcountll(x);}
int dp[N],dp1[N],dp2[2][N];
int tmp[N],tmp2[N][10];
int ans[N];
void solve(){	
	string s;
	int m;
	cin>>s>>m;
	int n=s.length();
	for(int i=0;i<(1<<n);i++){
		dp[0]=i&1;
		for(int j=1;j<n;j++)dp[j]=dp[j-1]+((i>>j)&1);
		for(int ch=0;ch<4;ch++){
			dp1[0]=dp[0];
			if(ch==tmp[s[0]]) dp1[0]=1;
			for(int j=1;j<n;j++){
				dp1[j]=max(dp1[j-1],dp[j]);
				if(ch==tmp[s[j]])dp1[j]=max(dp1[j],dp[j-1]+1);
			}
			int t=0; 
			t|=dp1[0];
			for(int j=1;j<n;j++)t|=(dp1[j]-dp1[j-1])<<j;
			tmp2[i][ch]=t;
		}
	}
	memset(dp2,0,sizeof dp2);
	dp2[1][0]=1;
	for(int i=0;i<m;i++){
		for(int j=0;j<(1<<n);j++)dp2[i&1][j]=0;
		for(int j=0;j<(1<<n);j++){
			if(dp2[(i+1)&1][j]==0)continue;
			for(int ch=0;ch<4;ch++)dp2[i&1][tmp2[j][ch]]=(dp2[i&1][tmp2[j][ch]]+dp2[(i+1)&1][j])%mod;
		}
	}
	memset(ans,0,sizeof ans);
	for(int i=0;i<(1<<n);i++) ans[popc(i)]=(ans[popc(i)]+dp2[(m+1)&1][i])%mod;
	for(int i=0;i<=n;i++)cout<<ans[i]<<"\n";
}
signed main(){
	tmp['A']=0,tmp['C']=1,tmp['G']=2,tmp['T']=3;
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
