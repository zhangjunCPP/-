#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1<<30;
struct node{int v,w,nex,val;}a[N];
int first[N],cnt=1;
void add(int u,int v,int w,int val){
	a[++cnt]={v,w,first[u],val};
	first[u]=cnt;
}
void insert(int u,int v,int w,int val){
	add(u,v,w,val);
	add(v,u,0,-val);
}
int now[N],dis[N];
bool vis[N];
bool spfa(int s,int t){
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	queue<int> q;
	q.push(s);
	now[s]=first[s];
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(a[i].w&&dis[v]>dis[u]+a[i].val){
				dis[v]=dis[u]+a[i].val;
				now[v]=first[v];
				q.push(v);
				vis[v]=true;
			}
		}
	}
	return dis[t]<dis[0];
}
int dinic(int u,int flow,int t){
	if(u==t) return flow;
	int have=flow;
	vis[u]=true;
	for(int i=first[u];i&&have;i=a[i].nex){
		now[u]=i;
		int v=a[i].v;
		if(!vis[v]&&a[i].w&&dis[v]==dis[u]+a[i].val){
			int tmp=dinic(v,min(a[i].w,have),t);
			if(tmp==0) dis[v]=-1;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	vis[u]=false;
	return flow-have;
}
int sum;
pair<int,int> solve(int s,int t){
	int ans1=0,ans2=0;
	while(spfa(s,t)){
		int tmp;
		while((tmp=dinic(s,INF,t)))ans1+=tmp,ans2+=tmp*dis[t]; 
	}
	return {ans1*2,ans2};
}
int n,m,s,t;
int f(int x,int y,int num){return (x-1)*m+y+num*n*m;}
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int dv[4]={3,4,1,2};
//中0上1右2下3左4
void build(int x,int y,int val){
	if((x+y)&1){
		insert(s,f(x,y,0),INF,0);
		for(int i=0;i<4;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(tx>=1&&tx<=n&&ty>=1&&ty<=m)insert(f(x,y,i+1),f(tx,ty,dv[i]),1,0);
		}
		for(int i=0;i<4;i++){
			if(val&(1<<i)){
				insert(f(x,y,0),f(x,y,i+1),1,0);
				sum++;
			}
		}
		switch(val){
		case 1:
			insert(f(x,y,1),f(x,y,2),1,1);
			insert(f(x,y,1),f(x,y,3),1,2);
			insert(f(x,y,1),f(x,y,4),1,1);
			break;
		case 2:
			insert(f(x,y,2),f(x,y,1),1,1);
			insert(f(x,y,2),f(x,y,3),1,1);
			insert(f(x,y,2),f(x,y,4),1,2);
			break;
		case 4:
			insert(f(x,y,3),f(x,y,1),1,2);
			insert(f(x,y,3),f(x,y,2),1,1);
			insert(f(x,y,3),f(x,y,4),1,1);
			break;
		case 8:
			insert(f(x,y,4),f(x,y,1),1,1);
			insert(f(x,y,4),f(x,y,2),1,2);
			insert(f(x,y,4),f(x,y,3),1,1);
			break;
		case 3:
			insert(f(x,y,1),f(x,y,3),1,1);
			insert(f(x,y,2),f(x,y,4),1,1);
			break;
		case 6:
			insert(f(x,y,3),f(x,y,1),1,1);
			insert(f(x,y,2),f(x,y,4),1,1);
			break;
		case 9:
			insert(f(x,y,1),f(x,y,3),1,1);
			insert(f(x,y,4),f(x,y,2),1,1);
			break;
		case 12:
			insert(f(x,y,3),f(x,y,1),1,1);
			insert(f(x,y,4),f(x,y,2),1,1);
			break;
		case 7:
			insert(f(x,y,1),f(x,y,4),1,1);
			insert(f(x,y,2),f(x,y,4),1,2);
			insert(f(x,y,3),f(x,y,4),1,1);
			break;
		case 11:
			insert(f(x,y,1),f(x,y,3),1,2);
			insert(f(x,y,2),f(x,y,3),1,1);
			insert(f(x,y,4),f(x,y,3),1,1);
			break;
		case 13:
			insert(f(x,y,1),f(x,y,2),1,1);
			insert(f(x,y,3),f(x,y,2),1,1);
			insert(f(x,y,4),f(x,y,2),1,2);
			break;
		case 14:
			insert(f(x,y,2),f(x,y,1),1,1);
			insert(f(x,y,3),f(x,y,1),1,2);
			insert(f(x,y,4),f(x,y,1),1,1);
			break;
		}
	}
	else {
		insert(f(x,y,0),t,INF,0);
		for(int i=0;i<4;i++){
			if(val&(1<<i)){
				insert(f(x,y,i+1),f(x,y,0),1,0);
				sum++;
			}
		}
		switch(val){
		case 1:
			insert(f(x,y,2),f(x,y,1),1,1);
			insert(f(x,y,3),f(x,y,1),1,2);
			insert(f(x,y,4),f(x,y,1),1,1);
			break;
		case 2:
			insert(f(x,y,1),f(x,y,2),1,1);
			insert(f(x,y,3),f(x,y,2),1,1);
			insert(f(x,y,4),f(x,y,2),1,2);
			break;
		case 4:
			insert(f(x,y,1),f(x,y,3),1,2);
			insert(f(x,y,2),f(x,y,3),1,1);
			insert(f(x,y,4),f(x,y,3),1,1);
			break;
		case 8:
			insert(f(x,y,1),f(x,y,4),1,1);
			insert(f(x,y,2),f(x,y,4),1,2);
			insert(f(x,y,3),f(x,y,4),1,1);
			break;
		case 3:
			insert(f(x,y,3),f(x,y,1),1,1);
			insert(f(x,y,4),f(x,y,2),1,1);
			break;
		case 6:
			insert(f(x,y,1),f(x,y,3),1,1);
			insert(f(x,y,4),f(x,y,2),1,1);
			break;
		case 9:
			insert(f(x,y,3),f(x,y,1),1,1);
			insert(f(x,y,2),f(x,y,4),1,1);
			break;
		case 12:
			insert(f(x,y,1),f(x,y,3),1,1);
			insert(f(x,y,2),f(x,y,4),1,1);
			break;
		case 7:
			insert(f(x,y,4),f(x,y,1),1,1);
			insert(f(x,y,4),f(x,y,2),1,2);
			insert(f(x,y,4),f(x,y,3),1,1);
			break;
		case 11:
			insert(f(x,y,3),f(x,y,1),1,2);
			insert(f(x,y,3),f(x,y,2),1,1);
			insert(f(x,y,3),f(x,y,4),1,1);
			break;
		case 13:
			insert(f(x,y,2),f(x,y,1),1,1);
			insert(f(x,y,2),f(x,y,3),1,1);
			insert(f(x,y,2),f(x,y,4),1,2);
			break;
		case 14:
			insert(f(x,y,1),f(x,y,2),1,1);
			insert(f(x,y,1),f(x,y,3),1,2);
			insert(f(x,y,1),f(x,y,4),1,1);
			break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	s=n*m*5+1;
	t=s+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			build(i,j,x);
		}
	}
	auto ans=solve(s,t);
	if(ans.first!=sum) puts("-1");
	else cout<<ans.second;
}