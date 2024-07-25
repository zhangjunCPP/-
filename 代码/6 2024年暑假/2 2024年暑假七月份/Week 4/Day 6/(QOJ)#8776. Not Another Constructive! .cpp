#include <bits/stdc++.h>
using namespace std;
const int N=45,K=2505;
string ans;
bitset<K>dp[N][N][N];
int main() {
	int n,m;
	string s;
	cin>>n>>m>>s;
	for(int i=0;i<=n;i++)dp[0][0][i][0]=true;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=i;j++) {
			for(int k=0;k<=n-i;k++) {
				if(s[i-1]=='N'||s[i-1]=='?')if(j)dp[i][j][k]|=dp[i-1][j-1][k];
				if(s[i-1]=='C'||s[i-1]=='?')dp[i][j][k]|=dp[i-1][j][k+1];
				if(s[i-1]=='A'||s[i-1]=='?')dp[i][j][k]|=dp[i-1][j][k]<<(j*k);
				if(s[i-1]!='N'&&s[i-1]!='C'&&s[i-1]!='A')dp[i][j][k]|=dp[i-1][j][k];
			}
		}
	}
	int pos=0;
	while(pos<=n&&!dp[n][pos][0][m])pos++;
	if(pos>n){cout<<"-1";return 0;}
	ans.resize(s.size());
	for(int i=n,j=pos,k=0,l=m;i;i--) {
		if(s[i-1]=='N'||(s[i-1]=='?'&&j&&dp[i-1][j-1][k][l]))j--,ans[i-1]='N';
		else if(s[i-1]=='C'||(s[i-1]=='?'&&dp[i-1][j][k+1][l]))k++,ans[i-1]='C';
		else if(s[i-1]=='A'||(s[i-1]=='?'&&l>=j*k&&dp[i-1][j][k][l-j*k]))l-=j*k,ans[i-1]='A';
		else ans[i-1]=(s[i-1]=='?'?'F':s[i-1]);
	}
	cout<<ans;
}