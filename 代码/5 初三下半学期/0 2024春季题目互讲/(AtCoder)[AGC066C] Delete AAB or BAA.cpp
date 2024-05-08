#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int dp[N];
int mx[3][N*3][2];
void solve(){
	string s;
	cin>>s;
	s="$"+s;
	int n=s.size()-1;
	for(int i=0;i<3;i++)for(int j=0;j<=n*3;j++)for(int k=0;k<2;k++)mx[i][j][k]=-0x3f3f3f3f;
	for(int i=0;i<=n;i++)dp[i]=0;
	int sum=n;
	mx[0][sum][s[1]=='B']=0;
	for(int i=1;i<=n;i++){
		sum+=(s[i]=='A'?-1:2);
		dp[i]=dp[i-1];
		if(s[i]=='A')dp[i]=max(dp[i],mx[i%3][sum][1]+i/3);
		else dp[i]=max(dp[i],max(mx[i%3][sum][0],mx[i%3][sum][1])+i/3);
		mx[i%3][sum][s[i+1]=='B']=max(mx[i%3][sum][s[i+1]=='B'],dp[i]-i/3);
	}
	cout<<dp[n]<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}