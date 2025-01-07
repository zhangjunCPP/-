#include<bits/stdc++.h>
using namespace std;
const double eps=1e-4;
const int N=3000+10;	
int k,n;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N];
struct node2{int s,p;}people[N];
double val[N];
double dp[N][N];
void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=val[u];
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v);
		for(int j=min(siz[u],k+1);j>=1;j--)for(int l=0;l<=min(siz[v],k+1);l++)dp[u][j+l]=max(dp[u][j+l],dp[u][j]+dp[v][l]);
		siz[u]+=siz[v];
	}
}
bool check(double mid){
	for(int i=1;i<=n;i++)val[i]=people[i].p-mid*people[i].s;
	for(int i=0;i<=n;i++)siz[i]=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=k+1;j++)dp[i][j]=-1e9;
	dfs(0);
	return dp[0][k+1]>0;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>k>>n;
	for(int i=1;i<=n;i++){
		cin>>people[i].s>>people[i].p;
		int fa;
		cin>>fa;
		add(fa,i);
	}
	double l=0,r=1e4;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.3lf",l);
}