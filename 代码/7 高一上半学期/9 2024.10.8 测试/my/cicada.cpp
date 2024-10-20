#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int x[N],y[N];
int dp[2][10][10];
int main(){
	int n,k;
	cin>>n>>k;
	bool flag=true;
	if(k>=8)flag=false;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(x[i]>=8||y[i]>=8)flag=false;
	}
	if(n<=10){
		int ans=-1;
		for(int S=1;S<(1<<n);S++){
			int sum_xor_x=0,sum_xor_y=0;
			for(int i=1;i<=n;i++){
				if((S>>(i-1))&1){
					sum_xor_x^=x[i];
					sum_xor_y^=y[i];
				}
			}
			if(sum_xor_x<=k)ans=max(ans,sum_xor_y);
		}
		cout<<ans;
		return 0;
	}
	if(flag){
		for(int i=1;i<=n;i++){
			for(int u=0;u<8;u++)for(int v=0;v<8;v++)dp[i&1][u][v]=(dp[(i-1)&1][u][v]||dp[(i-1)&1][u^x[i-1]][v^y[i-1]]);
			dp[i&1][x[i]][y[i]]=1;
		}
		for(int i=7;i>=0;i--){
			for(int j=0;j<=k;j++)if(dp[n&1][j][i]){
				cout<<i;
				return 0;
			}
		}
		cout<<"-1";
		return 0;
	}
	cout<<"-1";
}