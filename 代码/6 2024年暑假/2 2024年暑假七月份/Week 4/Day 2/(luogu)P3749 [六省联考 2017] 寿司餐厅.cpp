#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
	a[++cnt]=node{v,w,first[u]};
	first[u]=cnt;
}
int now[N];
int dis[N];
int bfs(int s,int t){
	memset(dis,0,sizeof dis);
	queue<int> q;
	q.push(s);
	dis[s]=1;
	now[s]=first[s];
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(!dis[v]&&a[i].w){
				dis[v]=dis[u]+1;
				now[v]=first[v];
				q.push(v);
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
int dinic(int u, int rest,int t){
	if(u==t) return rest;
	int have=rest;
	for(int i=now[u]; i&&have; i=a[i].nex){
		int v=a[i].v;
		now[u]=i;
		if(dis[v]== dis[u] + 1&&a[i].w){
			int tmp=dinic(v,min(have,a[i].w),t);
			if(!tmp) dis[v]=0;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return rest-have;
}
int w[120][120];
int d[N];
int vis[N];
int n,m;
int f(int x,int y){return (x-1)*n+y;}
int main(){
	int ans=0;
	int s=11101,t=11102;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>d[i],vis[d[i]]=1;
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)cin>>w[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int dx=1100+f(i,j),dy=1100+f(i+1,j),dz=1100+f(i,j-1);
			if(w[i][j]>0) {
				add(s,dx,w[i][j]);
				add(dx,s,0);
				ans+=w[i][j];
			}
			else {
				add(dx,t,-w[i][j]);
				add(t,dx,0);
			}
			if(i!=j){
				add(dx,dy,INF);
				add(dy,dx,0);
				add(dx,dz,INF);
				add(dz,dx,0);
			}
			else{
				add(dx,i,INF);
				add(i,dx,0);
			}
		}
		add(i,t,d[i]);add(t,i,0);
		add(i,100+d[i],INF);add(100+d[i],i,0);
	}
	if(m)for(int i=1;i<=1000;i++){
		if(vis[i]){
			add(100+i,t,i*i);
			add(t,100+i,0);
		}
	}
	while(bfs(s,t)){
		int tmp;
		while((tmp=dinic(s,INF,t))) ans-=tmp;
	}
	cout<<ans;
}