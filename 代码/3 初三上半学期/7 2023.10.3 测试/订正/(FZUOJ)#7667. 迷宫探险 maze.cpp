#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
vector<pair<int,int> > G[N]; 
struct node2{
	int id,val;
	bool operator<(const node2 &b) const {return val>b.val;} 
};
priority_queue<node2> q;
bool vis[N];
int dis[N];
int d[N];
bool cmp(const pair<int,int> &a,const pair<int,int> &b){return a.second<b.second;}
int main(){
	memset(dis,0x3f,sizeof dis);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) {
		int x; 
		cin>>x;
		q.push({x,0});
		dis[x]=0;
	}
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<=m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end(),cmp);
	while(!q.empty()){
		node2 now=q.top();
		q.pop();
		int u=now.id;
		if(dis[u]!=0&&d[u]){
			d[u]--;
			continue;
		}
		dis[u]=min(dis[u],now.val);
		if(vis[u]) continue;
		vis[u]=true;
		for(auto now:G[u]){
			int v=now.first;
			int w=now.second;
			if(dis[v]>dis[u]+w){
				q.push({v,dis[u]+w});
				
			}
		}
	}
	if(dis[1]==0x3f3f3f3f) puts("-1");
	else cout<<dis[1];
} 
