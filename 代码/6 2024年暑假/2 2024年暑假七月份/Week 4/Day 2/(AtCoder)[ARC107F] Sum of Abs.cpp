#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int INF=1e18;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v,int w){add(u,v,w),add(v,u,0);}
int dis[N],now[N];
bool bfs(int s,int t){
	queue<int> q;
	memset(dis,0,sizeof dis);
	dis[s]=1;
	now[s]=first[s];
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(a[i].w&&!dis[v]){
				dis[v]=dis[u]+1;
				now[v]=first[v];
				q.push(v);
			}
		}
	}
	return dis[t]!=0;
}
int dinic(int s,int flow,int t){
	if(s==t)return flow;
	int have=flow;
	for(int i=now[s];i&&have;i=a[i].nex){
		now[s]=i;
		int v=a[i].v;
		if(a[i].w&&dis[v]==dis[s]+1){
			int tmp=dinic(v,min(a[i].w,have),t);
			if(!tmp) dis[v]=-1;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return flow-have;
}
int calc(int s,int t){
	int ans=0;
	while(bfs(s,t)){
		int tmp;
		while((tmp=dinic(s,INF,t)))ans+=tmp;
	}
	return ans;
}
int val1[N],val2[N];
signed main() {
	int n,m;
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=n;i++)cin>>val1[i];
	for(int i=1;i<=n;i++)cin>>val2[i],ans+=abs(val2[i]);
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add_edge(u+n,v,INF);
		add_edge(v+n,u,INF);
	}
	int s=n*2+1;
	int t=s+1;
	for(int i=1;i<=n;i++) {
		add_edge(i,i+n,val1[i]+abs(val2[i]));
		if(val2[i]>=0)add_edge(s,i,val2[i]*2);
		else add_edge(i+n,t,-val2[i]*2);
	}
	cout<<ans-calc(s,t);

}