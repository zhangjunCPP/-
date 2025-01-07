#include <bits/stdc++.h>
using namespace std;
const int mod=10007;
const int N=1005;
int dp[N][N];
void solve(int tmp){
	string s;
	cin>>s;
	int siz=s.size();
	memset(dp,0,sizeof dp);
	for(int i=0;i<siz;i++)dp[i][i]=1;
	for(int i=0;i<siz-1;i++) dp[i][i+1]=(s[i]==s[i+1]?3:2);
	for(int len=3;len<=siz;len++){
		for(int i=0;i+len-1<siz;i++){
			int j=i+len-1;
			dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
			if(s[i]==s[j]) dp[i][j]=(dp[i][j]+dp[i+1][j-1]+1)%mod;
		}
	}
	cout<<"Case "<<tmp<<": ";
	cout<<dp[0][siz-1]<<"\n";

}
signed main(){
	int T;
	cin>>T;
	int tmp=0;
	while(T--)solve(++tmp);
}