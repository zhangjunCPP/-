#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
double x[2000],y[2000];
void math(double &a,double &b,int i,int j){
	a=(y[i]*x[j]-y[j]*x[i])/(x[i]*x[i]*x[j]-x[i]*x[j]*x[j]);
	b=(y[i]*x[j]*x[j]-y[j]*x[i]*x[i])/(x[i]*x[j]*x[j]-x[i]*x[i]*x[j]);
}
int dp[1<<20];
int line[20][20];
int cnt;
int tmp[1<<20];
void solve(){
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	memset(line,0,sizeof line);
	cnt=0;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			double a,b;
			math(a,b,i,j);
			if(a>-eps) continue;
			for(int k=1;k<=n;k++)if(x[k]*x[k]*a+x[k]*b-y[k]>-eps&&x[k]*x[k]*a+x[k]*b-y[k]<eps)line[i][j]|=1<<(k-1);
		}
	}

	for(int i=0;i<(1<<n);i++){
		int j=tmp[i];
		dp[i|(1<<(j-1))]=min(dp[i|(1<<(j-1))],dp[i]+1);
		for(int k=1;k<=n;k++){
			dp[i|line[j][k]]=min(dp[i|line[j][k]],dp[i]+1);
		}
	}
	cout<<dp[(1<<n)-1]<<"\n";
}
void init(){
	for(int i=0;i<(1<<18);i++){
		int ans=1;
		for(;ans<=18&&(i&(1<<(ans-1)));ans++);
		tmp[i]=ans;
	}
}
int main(){
	init();
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}