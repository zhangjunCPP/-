#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f;
struct node{
	int v,w,val,nex;
}a[N];
int first[N],cnt=1;
int now[N];
bool vis[N];
int dis[N];
bool spfa(int s,int t){
	queue<int> q;
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	q.push(s);
	now[s]=first[s];
	dis[s]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(a[i].w){
				if(dis[v]>dis[u]+a[i].val){
					now[v]=first[v];
					dis[v]=dis[u]+a[i].val;
					if(!vis[v])q.push(v),vis[v]=true;
				}
			}
		}
	}
	return dis[t]!=dis[0];
}
int dinic(int u,int flow,int t){
	if(u==t)return flow;
	int have=flow;
	vis[u]=true;
	for(int i=now[u];i&&have;i=a[i].nex){
		now[u]=i;
		int v=a[i].v;
		if(vis[v]||dis[v]!=dis[u]+a[i].val||!a[i].w)continue;
		int tmp= dinic(v,min(a[i].w,have),t);
		if(!tmp)dis[v]=-1;
		a[i].w-=tmp;
		a[i^1].w+=tmp;
		have-=tmp;
	}
	vis[u]=false;
	return flow-have;
}
pair<int,int> calc(int s,int t){
	int ans1=0,ans2=0;
	while(spfa(s,t)){
		int flow=0;
		while((flow=dinic(s,0x3f3f3f3f,t)))ans1+=flow,ans2+=flow*dis[t];
	}
	return {ans1,ans2};
}
void add(int u,int v,int w,int val){
	a[++cnt]={v,w,val,first[u]};
	first[u]=cnt;
}
int flow[N];
void add_edge(int u,int v,int l,int r,int w){
	flow[v]+=l,flow[u]-=l;
	add(u,v,r-l,w);
	add(v,u,0,-w);
}
int main(){
	int n1,n2,m,R,B;
	cin>>n1>>n2>>m>>R>>B;
	int s=n1+n2+1,t=n1+n2+2;
	int S=t+1,T=t+2;
	string s1,s2;
	cin>>s1>>s2;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add_edge(u,v+n1,0,1,R);
		add_edge(v+n1,u,0,1,B);
	}
	for(int i=0;i<n1;i++){
		if(s1[i]=='R')add_edge(s,i+1,1,INF,0);
		else if(s1[i]=='B')add_edge(i+1,t,1,INF,0);
		else add_edge(s,i+1,0,INF,0), add_edge(i+1,t,0,INF,0);
	}
	for(int i=0;i<n2;i++){
		if(s2[i]=='R')add_edge(i+1+n1,t,1,INF,0);
		else if(s2[i]=='B')add_edge(s,i+1+n1,1,INF,0);
		else add_edge(s,i+1+n1,0,INF,0), add_edge(i+1+n1,t,0,INF,0);
	}
	add_edge(t,s,0,INF,0);
	int sum=0;
	for(int i=1;i<=t;i++){
		if(flow[i]>0)sum+=flow[i],add(S,i,flow[i],0),add(i,S,0,0);
		else add(i,T,-flow[i],0),add(T,i,0,0);
	}
	pair<int,int> ans= calc(S,T);
	if(ans.first!=sum){puts("-1");return 0;}
	cout<<ans.second<<"\n";
	for(int i=2;i<m*4+2;i+=4){
		if(!a[i].w)putchar('R');
		else if(!a[i+2].w)putchar('B');
		else putchar('U');
	}
}