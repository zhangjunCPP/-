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
int sum[N];
bool vis[N];
bool SPFA(int n){
	queue<int> q;
	q.push(1);
	dis[1]=0;
	vis[1]=true;
	sum[1]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				sum[v]=sum[u]+1;
				if(sum[v]>n)return true;
				if(!vis[v]){
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
	return false;
}
void init(){
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	memset(first,0,sizeof first);
	cnt=0;
}
void solve(){
	init();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		if(w>=0)add(u,v,w),add(v,u,w);
		else add(u,v,w);
	}
	puts(SPFA(n)?"YES":"NO");
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
}