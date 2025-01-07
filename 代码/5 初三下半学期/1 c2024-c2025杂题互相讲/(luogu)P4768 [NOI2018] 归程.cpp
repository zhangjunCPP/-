#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,m;
struct node{int v,w,nex;}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
struct node2{int u,v,l,a;}G[N];
struct node3{
	int id,val;
	bool operator<(const node3&oth)const{return val>oth.val;}
};
int dis[N];
bool vis[N];
void dij(){
	priority_queue<node3>q;
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	dis[1]=0;
	q.push({1,0});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				q.push({v,dis[v]});
			}
		}
	}
}
int fa[N];
int find(int x){if(fa[x]!=x)fa[x]=find(fa[x]);return fa[x];}
bool cmp(const node2&x,const node2&y){return x.a>y.a;}
int val[N];
int Min[N];
int fa2[N][20];
void dfs(int u,int dad){
	fa2[u][0]=dad;
	for(int i=1;i<20;i++)fa2[u][i]=fa2[fa2[u][i-1]][i-1];
	if(u<=n)Min[u]=dis[u];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v,u);
		Min[u]=min(Min[u],Min[v]);
	}
}
int calc(int u,int p){
	for(int i=19;i>=0;i--)if(val[fa2[u][i]]>p)u=fa2[u][i];
	return u;
}
void init(){
	memset(Min,0x3f,sizeof Min);
	memset(first,0,sizeof first);
	cnt=0;
}
void solve(){
	init();
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>G[i].u>>G[i].v>>G[i].l>>G[i].a;
		add(G[i].u,G[i].v,G[i].l);
		add(G[i].v,G[i].u,G[i].l);
	}
	dij();
	memset(first,0,sizeof first);
	cnt=0;
	sort(G+1,G+m+1,cmp);
	for(int i=1;i<n*2;i++)fa[i]=i;
	int tot=n;
	for(int i=1;i<=m;i++){
		int fu=find(G[i].u),fv=find(G[i].v);
		if(fu!=fv){
			fa[fu]=fa[fv]=++tot;
			val[tot]=G[i].a;
			add(tot,fu,0),add(tot,fv,0);
			if(tot==n*2-1)break;
		}
	}
	dfs(tot,0);
	int q,K,S;
	cin>>q>>K>>S;
	int lastans=0;
	while(q--){
		int v,p;
		cin>>v>>p;
		v=(v+K*lastans-1)%n+1;
		p=(p+K*lastans)%(S+1);
		lastans=Min[calc(v,p)];
		cout<<lastans<<"\n";
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}