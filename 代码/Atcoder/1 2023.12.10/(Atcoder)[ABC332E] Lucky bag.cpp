#include<bits/stdc++.h>
using namespace std;
const int N=17;
double dp[1<<N][N];
double w[N];
int main(){
	int n,d;
	cin>>n>>d;
	double sum=0;
	for(int i=0;i<n;i++){
		cin>>w[i];
		sum+=w[i];
	}
	sum/=d;
	for(int i=0;i<(1<<n);i++) {
		int tmp=0;
		for(int j=0;j<n;j++) if((i&(1<<j))) tmp+=w[j];
		dp[i][1]=(tmp-sum)*(tmp-sum);
		for(int j=2;j<=d;j++) {
			dp[i][j]=dp[i][j-1]+dp[0][1];
			for(int k=i;k;k=(k-1)&i){
				dp[i][j]=min(dp[i][j],dp[i-k][j-1]+dp[k][1]);	
			}
		}
	}
	printf("%.10lf",dp[(1<<n)-1][d]/d);
	return 0;
}
