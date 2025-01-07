#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,INF=1<<30;
struct noded{
	int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
void insert(int u,int v,int w){
	add(u,v,w);
	add(v,u,0);
}
int now[N],dis[N];
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
	return dis[t];
}
int dinic(int u,int flow,int t){
	if(u==t) return flow;
	int have=flow;
	for(int i=now[u];i&&have;i=a[i].nex){
		now[u]=i;
		int v=a[i].v;
		if(a[i].w&&dis[v]==dis[u]+1){
			int tmp=dinic(v,min(have,a[i].w),t);
			if(tmp==0) dis[v]=-1;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return flow-have;
}
int solve(int s,int t){
	int ans=0;
	while(bfs(s,t)){
		int tmp;
		while((tmp=dinic(s,INF,t))) ans+=tmp;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m,s,t;
	cin>>n>>m;
	s=n*2+1;t=s+1;
	for(int i=1;i<=n;i++) insert(s,i,1),insert(i+n,t,1),insert(i+n,i,INF);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		insert(a,b+n,INF);
	}
	cout<<n-solve(s,t);
}