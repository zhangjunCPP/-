/*
�о�T2�ȽϺ�д����
ֱ��DP
dp[i][j]��ʾ��j�����ճ�i�Ĵ�
ÿ��ö����һ��ת�Ƶ���
ʱ�临�Ӷ�  O(n^3)

45pts
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[405][405];
signed main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m,mod;
	cin>>n>>m>>mod;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=min(i,m);j++)for(int k=1;k<=i-j+1;k++)dp[i][j]=(dp[i][j]+dp[i-k][j-1]*k%mod)%mod;
	cout<<dp[n][m]%mod;
	return 0;
}
