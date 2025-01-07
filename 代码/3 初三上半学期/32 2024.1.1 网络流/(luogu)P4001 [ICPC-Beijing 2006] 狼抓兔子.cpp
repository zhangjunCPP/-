#include <bits/stdc++.h>
using namespace std;
int n,m;
struct node{
	int v,w,nex;
}a[10000000];
int first[10000000],cnt=1;
void add(int u,int v,int w){
	a[++cnt]=node{v,w,first[u]};
	first[u]=cnt;
}
int s,t;
int now[1000000];//弧优化
int dis[1000000];
int bfs(){
	memset(dis,0,sizeof dis);
	queue<int> bfs;
	bfs.push(s);
	dis[s]=1;
	now[s]=first[s];
	while(!bfs.empty()){
		int u=bfs.front();
		bfs.pop();
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(!dis[v]&&a[i].w){
				dis[v]=dis[u]+1;
				now[v]=first[v];
				bfs.push(v);
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
int dinic(int u, int rest){
	if(u==t) return rest;
	int have=rest;
	for(int i=now[u]; i&&have; i=a[i].nex){
		int v=a[i].v;
		now[u]=i;
		if(dis[v]== dis[u] + 1&&a[i].w){
			int tmp=dinic(v,min(have,a[i].w));
			if(!tmp) dis[v]=0;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return rest - have;
}
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int f(int i,int j){return (i-1)*m+j;}
int main(){
	cin>>n>>m;
	int tmp;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m-1;j++){
			cin>>tmp;
			add(f(i,j),f(i,j+1),tmp),add(f(i,j+1),f(i,j),tmp);
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m;j++){
			cin>>tmp;
			add(f(i,j),f(i+1,j),tmp),add(f(i+1,j),f(i,j),tmp);
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m-1;j++){
			cin>>tmp;
			add(f(i,j),f(i+1,j+1),tmp),add(f(i+1,j+1),f(i,j),tmp);
		}
	}
	s=f(1,1);
	t=f(n,m);
	int ans=0;
	while(bfs()){
		while(tmp= dinic(s,0x3f3f3f3f)) ans+=tmp;
	}
	cout<<ans;

}