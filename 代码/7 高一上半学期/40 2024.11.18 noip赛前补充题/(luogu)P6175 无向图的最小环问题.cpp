#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=400+10,INF=1e13;
int val[N][N];
int dis[N][N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)val[i][j]=INF;
		val[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		val[u][v]=val[v][u]=w;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=val[i][j];
	int ans=INF;
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++)ans=min(ans,dis[i][j]+val[i][k]+val[k][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	if(ans==INF)cout<<"No solution."<<endl;
	else cout<<ans;
}