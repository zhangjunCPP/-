#include <bits/stdc++.h>
using namespace std;
int d,p,q,r,s,t;
int val[55][55][55];
struct node{
	int v,w,nex;
}a[10000000];
int first[10000000],cnt=1;
void add(int u,int v,int w){
	a[++cnt]=node{v,w,first[u]};
	first[u]=cnt;
}
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
int f(int i,int j,int k){return (i-1)*p*q+(j-1)*q+k;}
int main(){
	cin>>p>>q>>r>>d;
	for(int i=1;i<=r;i++)for(int j=1;j<=p;j++)for(int k=1;k<=q;k++)cin>>val[i][j][k];
	s=p*q*r+1;
	t=p*q*r+2;
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			add(s,f(1,i,j),10000),add(f(1,i,j),s,0);
	for(int i=1;i<r;i++)
		for(int j=1;j<=p;j++)
			for(int k=1;k<=q;k++)
				add(f(i,j,k),f(i+1,j,k),val[i][j][k]),add(f(i+1,j,k),f(i,j,k),0);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			add(f(r,i,j),t,val[r][i][j]),add(t,f(r,i,j),0);
	for(int i=1;i+d<=r;i++)
		for(int j=1;j<=p;j++)
			for(int k=1;k<=q;k++)
				for(int l=0;l<4;l++)
					if(j+dx[l]>=1&&j+dx[l]<=p&&k+dy[l]>=1&&k+dy[l]<=q)
						add(f(i+d,j,k),f(i,j+dx[l],k+dy[l]),1e9),add(f(i,j+dx[l],k+dy[l]),f(i+d,j,k),0);
	int ans=0,tmp;
	while(bfs()){
		while(tmp= dinic(s,0x3f3f3f3f)) ans+=tmp;
	}
	cout<<ans;

}