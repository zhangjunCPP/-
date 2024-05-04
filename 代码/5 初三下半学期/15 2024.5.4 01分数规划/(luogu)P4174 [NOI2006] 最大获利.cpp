#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{int v,w,nex;}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v,int w){add(u,v,w);add(v,u,0);}
bool vis[N];
int dis[N];
int now[N];
bool bfs(int s,int t){
	for(int i=0;i<=t;i++)dis[i]=0,vis[i]=false;
	queue<int> q;
	now[s]=first[s];
	dis[s]=1;
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=a[i].nex){
			if(a[i].w){
				int v=a[i].v;
				if(!vis[v]){
					vis[v]=true;
					dis[v]=dis[u]+1;
					now[v]=first[v];
					q.push(v);
					if(v==t)return true;
				}
			}
		}
	}
	return false;
}
int dinic(int s,int val,int t){
	if(s==t)return val;
	int flow=val;
	for(int i=now[s];i&&flow;i=a[i].nex){
		now[s]=i;
		int v=a[i].v;
		if(a[i].w&&dis[v]==dis[s]+1){
			int tmp=dinic(v,min(a[i].w,flow),t);
			if(!tmp)dis[v]=-1;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			flow-=tmp;
		}
	}
	return val-flow;
}
int max_flow(int s,int t){
	int ans=0;
	while(bfs(s,t)){
		int tmp;
		while((tmp=dinic(s,1e9,t)))ans+=tmp;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	int sum=0;
	int s=n+m+1,t=n+m+2;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		add_edge(i+m,t,x);
	}
	for(int i=1;i<=m;i++){
		int u,v,x;
		cin>>u>>v>>x;
		sum+=x;
		add_edge(i,u+m,1e9);
		add_edge(i,v+m,1e9);
		add_edge(s,i,x);
	}
	cout<<sum-max_flow(s,t);
}