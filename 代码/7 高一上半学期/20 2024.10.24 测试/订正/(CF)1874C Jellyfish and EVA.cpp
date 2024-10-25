#include<bits/stdc++.h>
using namespace std;
const int N=5000+10;
struct node{
	int v,nex;
}a[N*100];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
double g[N][N];
void init(){
	g[1][1]=1;g[2][1]=0.5;
	for(int i=3;i<N;i++){
		g[i][1]=1.0/i;
		for(int j=2;j<=i;j++)g[i][j]=(j-2)*g[i-2][j-2]/i+(i-j)*g[i-2][j-1]/i;
	}
}
double dp[N];
int tmp[N],tot;
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)first[i]=0;
	cnt=0;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++)dp[i]=0;
	dp[n]=1;
	for(int i=n-1;i;i--){
		tot=0;
		for(int j=first[i];j;j=a[j].nex)tmp[++tot]=a[j].v;
		sort(tmp+1,tmp+tot+1,[](const int&x,const int&y){return dp[x]>dp[y];});
		for(int j=1;j<=tot;j++)dp[i]+=dp[tmp[j]]*g[tot][j];
	}
	printf("%.9lf\n",dp[1]);
}
int main(){
	init();
	int T;
	cin>>T;
	while(T--)solve();
}