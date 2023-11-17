#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n;
double p[N]; 
double sum[N];
double dp[N][N];
double dfs(int x,int y){
	if(dp[x][y]!=-1) return dp[x][y];
	if(x==y){
		dp[x][y]=sum[x]*(n-x)*1.0/n;
		return dp[x][y];
	}
	double tmp=(sum[x]-sum[x-y])*(n-x)*1.0/n;
	for(int i=1;i<=x-y;i++) {
		dp[x][y]=max(dp[x][y],dfs(x-y,i)+(1-dfs(x-y,i))*tmp);
	}
	return dp[x][y];
}
int main(){
	freopen("rescue.in","r",stdin);
	freopen("rescue.out","w",stdout);
	cin>>n;
//	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[i][j]=-1;
	for(int i=1;i<=n;i++) cin>>p[i],sum[i]=sum[i-1]+p[i];
//	for(int i=1;i<=n;i++) cout<<sum[i]<<" ";
//	cout<<"\n";
//	dp[1][1]=0;
//	for(int i=2;i<=n;i++) {
//		for(int j=1;j<=i;j++) {
//			if(i==j) dp[i][j]=sum[i]*(n-i)/n;
//			for(int k=1;k<=i-j;k++) {
//				dp[i][j]=max(dp[i][j],(1-dp[i-j][k])*(sum[i]-sum[i-j])*(n-i)/n);
//			}
//		}
//	}
	double ans=0;
	for(int i=1;i<=n;i++){
//		for(int j=1;j<=i;j++) {
			double tmp=sum[i]*(n-i)/n;
//			cout<<tmp<<" ";
			ans=max(ans,tmp);
//		}
//		cout<<"\n";
//		ans=max(ans,dp[i][i]);
	} 
	printf("%.10lf",ans);
//	for(int i=1;i<=n;i++) {
//		cout<<sum[i]*(n-i)/n<<" ";
//	}
	return 0;
}
/*
dp[i][j] 表示前i个人，但只出动了j个人 


7
0.5 0.5 0 0 0 0 0

0.71428571428571430157

------------

7
0.537354 0.277078 0.124580 0.046589 0.012498 0.001853 0.000048

0.59878460205905026381



0
0.197913 0.581737
0.0570994 0.229519 0.536578
0.0188266 0.0588396 0.192106 0.4224
0.00350363 0.015918 0.0420906 0.131641 0.285171
0.000263787 0.00201155 0.00820862 0.0212576 0.0660854 0.14285
0 0 0 0 0 0 0
*/
