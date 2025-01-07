#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f;
struct node{int v,w,nex;}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){a[++cnt]={v,w,first[u]};first[u]=cnt;}
void insert(int u,int v,int w){add(u,v,w),add(v,u,0);}
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
map<int,int> mp;
int l[N],r[N];
int need[N];
bool flag[N];
vector<int> G[N];
void init(){
	for(int i=0;i<N;i++) G[i].clear();
	mp.clear();
	cnt=1;
	memset(first,0,sizeof first);
	memset(need,0,sizeof need);
	memset(flag,false,sizeof flag);
}
int ans[N];
void solve(){
	init();
	int s=N-5;
	int t=s+1;
	int n,m,x,y;
	cin>>n>>m>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		mp[l[i]]=mp[r[i]]=1;
	}
	for(int i=1+n;i<=m+n;i++){
		cin>>l[i]>>r[i];
		mp[l[i]]=mp[r[i]]=1;
	}
	int tot=0;
	for(auto &it:mp)it.second=++tot;
	for(int i=1;i<=n+m;i++){
		l[i]=mp[l[i]],r[i]=mp[r[i]];
		need[l[i]]++,need[r[i]]--;
		G[l[i]].push_back(i);
	}
	for(int i=1;i<=tot;i++) need[i]+=need[i-1];
	insert(s,1,y);
	insert(tot,t,y);
	for(int i=1;i<tot;i++){
		if(x+y<need[i]) {puts("NO");return;}
		insert(i,i+1,min(y,x+y-need[i]));
	}
	for(int i=1+n;i<=m+n;i++)insert(l[i],r[i],1);
	if(calc(s,t)!=y){puts("NO");return;}
	puts("YES");
	queue<int> q1,q2;
	for(int i=1;i<=x;i++) q1.push(i);
	for(int i=1+x;i<=y+x;i++) q2.push(i);
	int tmp=cnt-1;
	for(int i=m+n;i>n;i--,tmp-=2) flag[i]=a[tmp].w;
	for(int i=1;i<=tot;i++){
		for(int now:G[i]){
			if(now<0){
				if(-now<=x)q1.push(-now);
				else q2.push(-now);
			}
		}
		for(int now:G[i]){
			if(now>0){
				if(now<=n||flag[now]) ans[now]=q1.front(),q1.pop();
				else ans[now]=q2.front(),q2.pop();
				G[r[now]].push_back(-ans[now]);
			}
		}
	}
	for(int i=1;i<=m+n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}