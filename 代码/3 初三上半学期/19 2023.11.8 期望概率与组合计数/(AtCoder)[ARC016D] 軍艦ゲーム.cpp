#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10,M=1e6+10;
struct node{
	int v,nex;
}a[M*2];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int du1[N],du2[N];
int n,m,h;
int d[N];
double dp[N][N];
double check(double mid){
	memset(dp,0,sizeof dp);
	queue<int> q;
	for(int i=1;i<=n;i++) {
		du2[i]=du1[i];
		if(du2[i]==0) {
			q.push(i);
			for(int j=1;j<=h;j++) dp[i][j]=mid+h-j;
		}
	}
	for(int i=1;i<=h;i++) dp[n][i]=0;
	while(!q.empty()) {
		int now=q.front(); 
		q.pop();
		for(int i=1;i<=h;i++) if(now!=1)dp[now][i]=min(dp[now][i],mid+h-i);
		for(int i=first[now];i;i=a[i].nex){
			int v=a[i].v;
			for(int j=1;j<=d[now];j++) dp[v][j]+=mid+h-j;
			for(int j=d[now]+1;j<=h;j++) dp[v][j]+=(dp[now][j-d[now]]+1)/du1[v];
			du2[v]--;
			if(du2[v]==0) q.push(v);
		}
	}
	return dp[1][h];
}
int main(){
	cin>>n>>m>>h;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(v,u);
		du1[u]++;
	}
	for(int i=1;i<=n;i++) cin>>d[i];
	double ans=-1;
	double l=0,r=1e6+10;
	for(int i=1;i<=40;i++) {
		double mid=(l+r)/2;
		double tmp=check(mid);
		if(abs(tmp-mid)<=1e-9) {
			printf("%.6lf",ans);
			return 0;
		}
		else if(tmp<mid)ans=mid,r=mid;
		else l=mid;
	}
	printf("%.6lf",ans);
}
