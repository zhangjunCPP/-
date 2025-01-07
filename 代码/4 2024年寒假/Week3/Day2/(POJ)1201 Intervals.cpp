#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int dis[N];
bool vis[N];
void SPFA(int s){
	memset(dis,-0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	dis[s]=0;
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]<dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				if(!vis[v]){
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u++,v++;
		n=max({n,u,v});
		add(u-1,v,w);
	}
	for(int i=1;i<=n;i++)add(i-1,i,0),add(i,i-1,-1);
	SPFA(0);
	cout<<dis[n];
	return 0;
}