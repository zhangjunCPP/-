#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+10;
int n,m,s;
struct node{int v,nex;}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	deg[v]++;
}
vector<pair<int,int>> G[N];
struct node2{
	int id,val;
	bool operator<(const node2&oth)const{return val>oth.val;}
};
int dis[N];
bool vis[N];
void dij(){
	priority_queue<node2>q;
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	q.push({s,dis[s]});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(auto it:G[u]){
			if(dis[it.first]>dis[u]+it.second){
				dis[it.first]=dis[u]+it.second;
				q.push({it.first,dis[it.first]});
			}
		}
	}
	for(int i=1;i<=n;i++)for(auto it:G[i])if(dis[it.first]==dis[i]+it.second)add(i,it.first);
}
int dep[N];
int fa[N][20];
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
vector<int>G2[N];
void topsort(){
	for(int i=1;i<=n;i++)fa[i][0]=-1;
	queue<int> q;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		int dad=fa[now][0];
		G2[dad].emplace_back(now);
		dep[now]=dep[dad]+1;
		for(int i=1;i<20;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
		for(int i=first[now];i;i=a[i].nex){
			int v=a[i].v;
			if(fa[v][0]==-1)fa[v][0]=now;
			else fa[v][0]=LCA(fa[v][0],now);
			deg[v]--;
			if(!deg[v])q.push(v);
		}
	}
}
int siz[N];
void dfs(int u){
	siz[u]=1;
	for(int v:G2[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	dij();
	topsort();
	dfs(s);
	int ans=-1;
	for(int i=1;i<=n;i++)if(i!=s)ans=max(ans,siz[i]);
	cout<<ans;
}