#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int INF=1e18;
struct node{
	int v,w,val,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w,int val){
	a[++cnt]={v,w,val,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v,int w,int val){add(u,v,w,val);add(v,u,0,-val);}
int dis[N];
int now[N];
bool vis[N];
bool spfa(int s,int t){
	for(int i=1;i<=t;i++)dis[i]=INF;
	dis[s]=0;
	queue<int> q;
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		now[u]=first[u];
		for(int i=first[u];i;i=a[i].nex){
			if(a[i].w){
				int v=a[i].v;
				if(dis[v]>dis[u]+a[i].val){
					dis[v]=dis[u]+a[i].val;
					if(!vis[v])q.push(v),vis[v]=true;
				}
			}
		}
	}
	return dis[t]!=INF;
}
int dinic(int x,int val,int t){
	if(x==t)return val;
	vis[x]=true;
	int have=val;
	for(int i=now[x];i&&have;i=a[i].nex){
		now[x]=i;
		int v=a[i].v;
		if(!vis[v]&&a[i].w&&dis[v]==dis[x]+a[i].val){
			int tmp=dinic(v,min(have,a[i].w),t);
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
			if(!tmp)dis[v]=INF;
		}
	}
	vis[x]=false;
	return val-have;
}
int calc(int s,int t){
	int ans=0;
	while(spfa(s,t)){
		int tmp;
		while((tmp=dinic(s,INF,t)))ans+=tmp*dis[t];
	}
	return ans;
}
signed main() {
	int n,m,k;
	cin>>n>>m>>k;
	int p=n+m+1,s=p+1,t=s+1;
	for(int i=1;i<=n;i++)add_edge(s,i,m,0),add_edge(i,p,m-1,0);
	for(int i=1;i<=m;i++)add_edge(p,i+n,n-1,0),add_edge(i+n,t,n,0);
	while(k--){
		int u,v,w;
		cin>>u>>v>>w;
		add_edge(u,v+n,1,w);
	}
	cout<<calc(s,t);
}