#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node {
	int v,nex;
}a[N*10];
int first[N*10],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dis[N*10];
bool vis[N*10];
struct node2{
	int id,w;
	bool operator <(const node2 &b)const {
		return w>b.w;
	}
};
int dij(int s,int t) {
	priority_queue<node2> q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof vis);
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()) {
		int u=q.top().id;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push({v,dis[v]});
			}
		}
	}
	return dis[t]==0x3f3f3f3f?-1:dis[t];
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		for(int j=1;j<=x;j++) {
			int y;
			cin>>y;
			add(y,i+m+1);
			add(i+m+1,y);
		}
	}
	int ans=dij(1,m);
	if(ans==-1)cout<<"-1";
	else cout<<(ans-2)/2;
	return 0;
}