#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300+10;
const int mod=1e9+7;
bool vis[N];
int cnt,len[N];
int dp[N][N][N];
int sum1[N],sum2[N];
int pre[N][N][N];
signed main(){
	string s;
	cin>>s;
	int n=s.size();
	reverse(s.begin(),s.end());
	for(int i=0;i<n;i++){
		if(vis[i])continue;
		if(s[i]=='0'){cout<<0;return 0;}
		len[++cnt]=1;
		for(int j=i+1;j<n;j++){
			if(vis[j])continue;
			if(s[j]==(len[cnt]&1?'1':'0'))continue;
			len[cnt]++;
			vis[j]=true;
		}
	}
	for(int i=1;i<=n;i++)sum1[i]=sum1[i-1]+len[i]/2,sum2[i]=sum2[i-1]+(len[i]+1)/2;	
	int ans=0;
	dp[n][0][0]=1;
	for(int i=1;i<=n;i++){
		int tmp=n/(max(1ll,i-1));
		memset(pre[tmp+1],0,sizeof pre[tmp+1]);
		for(int j=tmp;j;j--){
			memcpy(pre[j],dp[j],sizeof pre[j]);
			memset(dp[j],0,sizeof dp[j]);
			for(int k=0;k<=n;k++)for(int l=0;l<=n;l++)pre[j][k][l]=(pre[j][k][l]+pre[j+1][k][l])%mod;
		}
		for(int j=1;j<=n/i;j++)for(int k=j/2;k<=sum1[i];k++)for(int l=(j+1)/2;l<=sum2[i];l++)dp[j][k][l]=pre[j][k-j/2][l-(j+1)/2];
		if(i>=cnt)for(int j=1;j<=n/i;j++)ans=(ans+dp[j][sum1[i]][sum2[i]])%mod;
	}
	cout<<ans;
}