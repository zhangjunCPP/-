#include <bits/stdc++.h>
using namespace std;
double dp[1005][1005];
int main(){
	int w,b;
	cin>>w>>b;
	for(int i=1;i<=w;i++){
		dp[i][0]=1.0;
		dp[i][1]=1.0*i/(i+1);
	}
	if(b==0|b==1){
		printf("%.9lf",dp[w][b]);
		return 0;
	}
	for(int i=1;i<=w;i++){
		for(int j=2;j<=b;j++){
			dp[i][j]=1.0*i/(i+j);
			dp[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(i)/(i+j-2)*dp[i-1][j-2];
			if(j>=3){
				dp[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*dp[i][j-3];
			}
		}
	}
	printf("%.9lf",dp[w][b]);
}