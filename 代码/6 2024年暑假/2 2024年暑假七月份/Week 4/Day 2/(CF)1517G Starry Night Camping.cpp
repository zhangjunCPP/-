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
int x[N],y[N];
int opt[N];
signed main() {
	int n;
	cin>>n;
	int s=0,t=2*n+1;
	int sum=0;
	for(int i=1;i<=n;i++) {
		int w;
		cin>>x[i]>>y[i]>>w;
		sum+=w;
		add_edge(i,n+i,w);
		if((x[i]&1)&&(y[i]&1))opt[i]=1,add_edge(s,i,INF);
		else if((!(x[i]&1))&&(y[i]&1))opt[i]=2;
		else if((!(x[i]&1))&&(!(y[i]&1)))opt[i]=3;
		else opt[i]=4,add_edge(n+i,t,INF);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(opt[j]==opt[i]+1&&abs(x[i]-x[j])+abs(y[i]-y[j])==1)add_edge(n+i,j,INF);
	cout<<sum-calc(s,t);
}