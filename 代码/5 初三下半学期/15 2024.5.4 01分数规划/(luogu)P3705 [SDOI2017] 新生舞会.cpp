#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const double eps=1e-7;
int n;
int a[N][N],b[N][N];
struct node{
	int v,w;
	double val;
	int nex;
}edge[N*50];
int first[N],cnt=1;
void add(int u,int v,int w,double val){
	edge[++cnt]={v,w,val,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v,int w,double val){add(u,v,w,val);add(v,u,0,-val);}
bool vis[N];
double dis[N];
int now[N];
bool spfa(int s,int t){
	for(int i=0;i<=t;i++)dis[i]=-1e9,vis[i]=false;
	queue<int> q;
	dis[s]=0;
	now[s]=first[s];
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=edge[i].nex){
			if(edge[i].w){
				int v=edge[i].v;
				if(dis[v]<dis[u]+edge[i].val){
					now[v]=first[v];
					dis[v]=dis[u]+edge[i].val;
					if(!vis[v])q.push(v),vis[v]=true;
				}
			}
		}
	}
	return dis[t]!=-1e9;
}
int dinic(int s,int val,int t){
	if(s==t)return val;
	vis[s]=true;
	int flow=val;
	for(int i=now[s];i;i=edge[i].nex){
		now[s]=i;
		int v=edge[i].v;
		if(!vis[v]&&edge[i].w&&dis[v]==dis[s]+edge[i].val){
			int tmp=dinic(v,min(edge[i].w,flow),t);
			if(!tmp)dis[v]=-1;
			edge[i].w-=tmp;
			edge[i^1].w+=tmp;
			flow-=tmp;
		}
	}
	vis[s]=false;
	return val-flow;
}
double max_flow(int s,int t){
	double ans=0;
	while(spfa(s,t)){
		int tmp;
		while((tmp=dinic(s,1e9,t)))ans+=tmp*dis[t];
	}
	return ans;
}
bool check(double mid){
	int s=2*n+1,t=2*n+2;
	for(int i=0;i<=t;i++)first[i]=0;
	cnt=1;
	for(int i=1;i<=n;i++)add_edge(s,i,1,0),add_edge(i+n,t,1,0);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)add_edge(i,j+n,1,a[i][j]*1.0-mid*b[i][j]*1.0);
	return max_flow(s,t)>0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>b[i][j];
	double l=0,r=1e5;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.6lf",l);
}