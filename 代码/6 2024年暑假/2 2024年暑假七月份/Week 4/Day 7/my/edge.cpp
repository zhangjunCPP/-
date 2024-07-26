#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+10;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
struct node2 {
	int id,val;
	bool operator<(const node2&oth)const {return val>oth.val;}
};
bool vis[N];
int dis[N];
signed main() {
	freopen("edge.in","r",stdin);
	freopen("edge.out","w",stdout);
	int n,m,A,B;
	cin>>n>>m>>A>>B;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v,A*2),add(v,u,A*2);
		add(u,v+n,B),add(v+n,u,B);
		add(v,u+n,B),add(u+n,v,B);
	}
	memset(dis,0x3f,sizeof dis);
	priority_queue<node2>q;
	dis[1]=0;
	q.push({1,0});
	while(!q.empty()) {
		auto now=q.top();
		q.pop();
		int u=now.id;
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex) {
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w) {
				dis[v]=dis[u]+a[i].w;
				q.push({v,dis[v]});
			}
		}
	}
	for(int i=2;i<=n;i++)cout<<dis[i]/2<<"\n";
}