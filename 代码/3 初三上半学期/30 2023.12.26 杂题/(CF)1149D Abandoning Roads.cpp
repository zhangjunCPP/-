#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
vector<pair<int,int> > G[N];
int fa[N],siz[N];
int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int u,int v){
	int fx=find(u),fy=find(v);
	if(fx!=fy){
		fa[fx]=fy;
		siz[fy]+=siz[fx];
	}
}
int id[N],tot;
long long dp[(1<<18)+50][75];
struct node{
	int S,u;
	long long val;
	bool operator<(const node &b) const{
		return val>b.val;
	}
};
priority_queue<node> q;
bool vis[(1<<18)+50][75];
int main(){
	memset(dp,0x3f,sizeof dp);
	int n,m,A,B;
	cin>>n>>m>>A>>B;
	for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
		if(w==A)merge(u,v);
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			if(siz[i]>3) id[i]=++tot;
			else id[i]=-1;
		}
	}
	tot++;
	for(int i=1;i<=n;i++) id[i]=id[find(i)];
	if(id[1]==-1) dp[0][1]=0;
	else dp[(1<<id[1])][1]=0;
	q.push({id[1]==-1?0:(1<<id[1]),1,0});
	while(!q.empty()){
		node now=q.top();
		q.pop();
		int u=now.u,S=now.S;
		if(vis[S][u]) continue;
		vis[S][u]=true;
		for(auto tmp:G[u]){
			int v=tmp.first,w=tmp.second;
			if(find(u)==find(v)&&w==B)continue;
			if(id[v]!=-1&&id[u]!=id[v]&&(S&(1<<id[v])))continue;
			int T=S|(id[v]==-1?0:(1<<id[v]));
			if(dp[T][v]>dp[S][u]+w){
				dp[T][v]=dp[S][u]+w;
				q.push({T,v,dp[T][v]});
			}
		}
	}
	for(int i=1;i<=n;i++){
		long long ans=1e18;
		for(int j=0;j<(1<<tot);j++)ans=min(ans,dp[j][i]);
		cout<<ans<<" ";
	}
}
