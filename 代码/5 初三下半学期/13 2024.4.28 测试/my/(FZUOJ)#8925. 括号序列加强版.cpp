#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;
int nex[N][N];
int dp[N];
int s[N];
int nex_2[600005][20];
signed main(){
	int n;
	cin>>n;
	int Max=-1;
	for(int i=0;i<n;i++)cin>>s[i],Max=max(Max,s[i]);
	if(Max<=15){
		memset(nex_2,-1,sizeof nex_2);
		for(int i=1;i<=n;i++) {
			int ch=s[i-1];
			nex_2[i][ch]=i-1;
			if(nex_2[i-1][ch]!=-1) {
				int j=nex_2[i-1][ch];
				dp[i]=dp[j]+1;
				for(int k=1;k<=20;k++)if(k!=ch)nex_2[i][k]=nex_2[j][k];
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++) ans+=dp[i];
		cout<<ans;
	}
	else{
		memset(nex,-1,sizeof nex);
		for(int i=1;i<=n;i++) {
			int ch=s[i-1];
			nex[i][ch]=i-1;
			if(nex[i-1][ch]!=-1) {
				int j=nex[i-1][ch];
				dp[i]=dp[j]+1;
				for(int k=1;k<=Max;k++) {
					if(k!=ch) nex[i][k]=nex[j][k];
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++) ans+=dp[i];
		cout<<ans;
	}
	return 0;
}