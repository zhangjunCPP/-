#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10,lim=30;
int a[N];
int dp[N][N][65];
int pos[N][N][65];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++){
		for(int j=-30;j<=30;j++)dp[i][i][j+lim]=a[i]*j,pos[i][i][j+lim]=i;
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l<=n-len+1;l++){
			int r=l+len-1;
			for(int i=-29;i<=29;i++){
				for(int j=pos[l][r-1][i+lim];j<=pos[l+1][r][i+lim];j++){
					int val1=dp[l][j][i-1+lim],val2=dp[j+1][r][i+1+lim];
					if(max(val1+a[j]+1,val2-(a[j]+1))<dp[l][r][i+lim]){
						dp[l][r][i+lim]=max(val1+a[j]+1,val2-(a[j]+1));
						pos[l][r][i+lim]=j;
					}
					if(max(val1+a[j+1],val2-a[j+1])<dp[l][r][i+lim]){
						dp[l][r][i+lim]=max(val1+a[j+1],val2-a[j+1]);
						pos[l][r][i+lim]=j;
					}
					int tmp=(val2-val1)/2;
					if(a[j]<tmp&&a[j+1]>=tmp&&max(val1+tmp,val2-tmp)<dp[l][r][i+lim]){
						dp[l][r][i+lim]=max(val1+tmp,val2-tmp);
						pos[l][r][i+lim]=j;
					}
				}
			}
		}
	}
	cout<<dp[1][n][0+lim];
}