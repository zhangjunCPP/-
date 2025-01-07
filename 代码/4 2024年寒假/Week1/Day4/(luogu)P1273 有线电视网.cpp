#include<bits/stdc++.h>
using namespace std;
const int N=3010;
int n,m;
struct node{
	int v,w,nex;
}a[N*2];
int cnt,first[N];
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int val[N];
int dp[N][N];
int siz[N];
int tmp[N];
void dfs(int u){
	dp[u][0]=0;
	if(u>n-m) dp[u][1]=val[u];
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v);
		for(int j=0;j<=siz[u]+siz[v]+10;j++) tmp[j]=-0x3f3f3f3f;
		for(int j=0;j<=siz[u];j++){
			for(int k=0;k<=siz[v];k++){
				int ans=dp[u][j]+dp[v][k]-a[i].w;
				if(k==0) ans+=a[i].w;
				tmp[j+k]=max(tmp[j+k],ans);
			}
		}
		siz[u]+=siz[v];
		for(int j=0;j<=siz[u]+1;j++) dp[u][j]=tmp[j];
	}
}
int main(){
	for(int i=0;i<N;i++)for(int j=0;j<N;j++) dp[i][j]=-0x3f3f3f3f;
	cin>>n>>m;
	for(int i=1;i<=n-m;i++){
		int k;
		cin>>k;
		while(k--){
			int v,w;
			cin>>v>>w;
			add(i,v,w);
		}
	}
	for(int i=n-m+1;i<=n;i++) cin>>val[i];
	dfs(1);
	for(int i=n;i>=0;i--)if(dp[1][i]>=0) {cout<<i;return 0;}
}
