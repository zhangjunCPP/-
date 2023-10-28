#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int to[N][27];
int dp[N];
signed main(){
	memset(to,-1,sizeof to);
	int n;
	string s;
	cin>>n>>s;
	for(int i=1;i<=n;i++) {
		int ch=s[i-1]-'a';
		to[i][ch]=i-1;
		if(to[i-1][ch]!=-1) {
			int j=to[i-1][ch];
			dp[i]=dp[j]+1;
			for(int k=0;k<26;k++) {
				if(k!=ch) to[i][k]=to[j][k];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans+=dp[i];
	cout<<ans;
	return 0;
}
