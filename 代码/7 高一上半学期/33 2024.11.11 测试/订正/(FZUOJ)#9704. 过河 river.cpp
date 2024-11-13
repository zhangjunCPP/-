#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e9;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
struct node2{
	int val,id;
	bool operator<(const node2&oth) const{return val>oth.val;}
};
bool vis[N];
int dis1[N],dis2[N];
int tot=0;
void dij(int s,int *dis){
	memset(dis,0x3f,sizeof (int)*(tot+5));
	memset(vis,false,sizeof vis);
	dis[s]=0;
	priority_queue<node2>q;
	q.push({dis[s],s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				q.push({dis[v],v});
			}
		}
	}
}
struct node3{int l,r,w,id;};
vector<node3>G[N];
struct node4{int l,r,w;};
vector<node4>G2[N];
int ans[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,l,r,w;
		cin>>x>>l>>r>>w;
		G[x].push_back({l,r,w,i});
	}
	for(int i=1;i<=n;i++){
		sort(G[i].begin(),G[i].end(),[](const node3&x,const node3&y){return x.l<y.l;});
		G2[i].push_back({0,0,++tot});
		for(auto it:G[i]){
			G2[i].back().r=it.l-1;
			G2[i].push_back({it.r+1,0,++tot});
			add(tot-1,tot,it.w);
			add(tot,tot-1,it.w);
		}
		G2[i].back().r=INF;
	}
	for(int i=1;i<n;i++){
		int x=0,y=0;
		while(x<G2[i].size()&&y<G2[i+1].size()){
			int l=max(G2[i][x].l,G2[i+1][y].l);
			int r=min(G2[i][x].r,G2[i+1][y].r);
			if(l<=r+1)add(G2[i][x].w,G2[i+1][y].w,0),add(G2[i+1][y].w,G2[i][x].w,0);
			if(G2[i][x].r<G2[i+1][y].r)x++;
			else y++;
		}
	}
	dij(G2[1][0].w,dis1);
	dij(G2[1].back().w,dis2);
	for(int i=1;i<=n;i++)
		for(int j=0;j<G[i].size();j++)
			ans[G[i][j].id]=min({dis1[G2[1].back().w],dis1[G2[i][j].w]+dis2[G2[i][j+1].w],dis2[G2[i][j].w]+dis1[G2[i][j+1].w]});
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}