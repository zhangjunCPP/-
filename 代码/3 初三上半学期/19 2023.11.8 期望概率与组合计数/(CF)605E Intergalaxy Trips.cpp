#include<bits/stdc++.h>
using namespace std;
const int N=1005;
double p[N][N];
double dp[N],g[N],h[N];
bool vis[N];
int main(){
	int n;
	cin>>n;
	if(n==1) {
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			int x;
			cin>>x;
			p[i][j]=x/100.0;
		}
	}
	dp[0]=1e9;
	for(int i=1;i<=n;i++) g[i]=h[i]=1;
	dp[n]=0;
	vis[n]=true;
	for(int i=1;i<=n;i++) {
		if(vis[i]) continue;
		g[i]+=p[i][n]*dp[n]*h[i];
		h[i]*=1-p[i][n];
		dp[i]=g[i]/(1-h[i]);
	}
	while(1){
		int id=0;
		for(int i=1;i<=n;i++) if(!vis[i]&&dp[i]<dp[id]) id=i;
		vis[id]=true;
		if(id==1){
			printf("%.8lf\n",dp[1]);
			return 0;
		}
		for(int i=1;i<=n;i++) {
			if(vis[i]) continue;
			g[i]+=p[i][id]*dp[id]*h[i];
			h[i]*=1-p[i][id];
			dp[i]=g[i]/(1-h[i]);
		}
	}
}