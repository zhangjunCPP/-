#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
const int N=5e6+10;
using namespace std;
struct node{
	int v,w,nex;
}a[N];
int cnt=1,first[N];
void add(int u,int v,int w){
	a[++cnt]=node{v,w,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v,int w) {add(u,v,w);add(v,u,0);}
int now[N];
int dis[N];
int bfs(int s,int t){
	memset(dis, false,sizeof dis);
	queue<int> q;
	q.push(s);
	dis[s]=1;
	now[s]=first[s];
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(a[i].w&&!dis[v]){
				q.push(v);
				now[v]=first[v];
				dis[v]=dis[u]+1;
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
int dinic(int x,int val,int t){
	if(x==t) return val;
	int have=val;
	for(int i=now[x];i&&have;i=a[i].nex){
		now[x]=i;
		int v=a[i].v;
		if(a[i].w&&dis[v]==dis[x]+1){
			int tmp= dinic(v,min(a[i].w,have),t);
			if(!tmp) dis[v]=0;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return val-have;
}
int solve(int s,int t){
	int ans=0;
	while(bfs(s,t)){
		int tmp;
		while((tmp=dinic(s,MAX,t)))ans+=tmp;
	}
	return ans;
}
int p[N],q[N];
int x[N],y[N];
int pos1[N],pos2[N],tot;
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i],p[i]++;
	for(int i=1;i<=n;i++)cin>>q[i],q[i]++;
	for(int i=1;i<=n;i++) {
		if(!x[i]) {
			x[i]=i;
			for(int j=p[i];j!=i;j=p[j])x[j]=i;
			if(p[i]!=i)pos1[i]=++tot;
		}
		if(!y[i]) {
			y[i]=i;
			for(int j=q[i];j!=i;j=q[j])y[j]=i;
			if(q[i]!=i)pos2[i]=++tot;
		}
	}
	int ans=n;
	int s=++tot,t=++tot;
	for(int i=1;i<=n;i++) {
		if(p[i]==i&&q[i]==i)ans--;
		else if(p[i]!=i&&q[i]!=i) {
			if(p[i]==q[i])add_edge(pos1[x[i]],pos2[y[i]],1),add_edge(pos2[y[i]],pos1[x[i]],1);
			else add_edge(pos1[x[i]],pos2[y[i]],1);
		}
		else {
			if(p[i]==i)add_edge(s,pos2[y[i]],1);
			else add_edge(pos1[x[i]],t,1);
		}
	}
	cout<<ans-solve(s,t);
}