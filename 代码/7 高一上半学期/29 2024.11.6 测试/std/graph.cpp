#include<bits/stdc++.h>
using namespace std;
int ans[10][10][10][10];
void solve(){
	int t,n,k,x,y;
	scanf("%d%d%d%d%d",&t,&n,&k,&x,&y);
	assert(0<=t&&t<=1000000000);
	assert(2<=n&&n<=1000000000);
	assert(1<=k&&k<=1000000000);
	assert(1<=x&&x<=n&&1<=y&&y<=n&&x!=y);
	if(t==0)return printf("%d\n",abs(x-y)),void();
	if(k==1)puts("1");
	else if(k==2){
		if(n==4&&t&1&&min(x,y)==2&&max(x,y)==3)puts("3");
		else if(n<=3){
			if(t==1)puts(abs(x-y)==2?"1":"-1");
			else puts("-1");
		}else{
			if(t&1)puts(abs(x-y)==1?"2":"1");
			else printf("%d\n",abs(x-y));
		}
	}else{
		bool a=abs(x-y)>=k,b=min(x,y)-k>=1||max(x,y)+k<=n;
		if(n<=8&&t<=5&&k==3)printf("%d\n",ans[n][t][x][y]);
		else if(k==3&&t==2&&!a&&!b&&min(x,y)+k<=n&&max(x,y)-k>=1)puts("1");
		else if(t==1&&!a&&!b&&min(x,y)+k<=n&&max(x,y)-k>=1)puts("3");
		else if(t>1)puts("-1");
		else if(a)puts("1");
		else if(b)puts("2");
		else puts("-1");
	}
}
int main(){
	for(int n=2;n<=8;n++){
		int G[10][10]{};
		for(int i=1;i<n;i++)G[i][i+1]=G[i+1][i]=1;
		for(int t=0;t<=5;t++){
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(!G[i][j])G[i][j]=1e9;
			for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
				ans[n][t][i][j]=G[i][j]<1e8?G[i][j]:-1;
			}
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
				G[i][j]=G[i][j]<1e8&&G[i][j]>=3;
			}
		}
	}
	int T;for(scanf("%d",&T),assert(1<=T&&T<=1000000);T--;)solve();
	return 0;
}