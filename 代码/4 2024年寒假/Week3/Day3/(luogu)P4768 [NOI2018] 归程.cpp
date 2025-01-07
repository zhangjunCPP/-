#include <bits/stdc++.h>

using namespace std;
const int N=5e6+10;
struct node{int v,w,nex;}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int n,m;
int dis[N];
bool vis[N];
struct node3{
	int id,val;
	bool operator<(const node3&other)const{return val>other.val;}
};
void dij(int s){
	priority_queue<node3> q;
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()){
		auto now=q.top();
		q.pop();
		int u=now.id;
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
struct node2{int u,v,l,a;}G[N];
bool cmp(const node2&x,const node2&y){return x.a>y.a;}
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int val[N];
int Min[N];
int fa2[N][20];
void dfs(int u,int dad){
	fa2[u][0]=dad;
	for(int i=1;i<=19;i++)fa2[u][i]=fa2[fa2[u][i-1]][i-1];
	if(u<=n)Min[u]=dis[u];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v,u);
		Min[u]=min(Min[u],Min[v]);
	}
}
void init(){
	memset(first,0,sizeof first);
	cnt=0;
	memset(Min,0x3f,sizeof Min);
}
int calc(int u,int x){
	for(int i=19;i>=0;i--)if(val[fa2[u][i]]>x)u=fa2[u][i];
	return u;
}
void solve(){
	init();
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>G[i].u>>G[i].v>>G[i].l>>G[i].a,add(G[i].u,G[i].v,G[i].l),add(G[i].v,G[i].u,G[i].l);
	dij(1);
	memset(first,0,sizeof first);
	cnt=0;
	sort(G+1,G+m+1,cmp);
	int tot=n;
	for(int i=1;i<(n<<1);i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int fu=find(G[i].u),fv=find(G[i].v);
		if(fu!=fv){
			val[++tot]=G[i].a;
			add(tot,fu,0),add(tot,fv,0);
			fa[fu]=fa[fv]=tot;
			if(tot==n*2-1)break;
		}
	}
	dfs(tot,0);
	int Q,K,S;
	cin>>Q>>K>>S;
	int last=0;
	while(Q--){
		int v,p;
		cin>>v>>p;
		v=(v+K*last-1)%n+1;
		p=(p+K*last)%(S+1);
		int now=calc(v,p);
		cout<<Min[now]<<"\n";
		last=Min[now];
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--)solve();
}