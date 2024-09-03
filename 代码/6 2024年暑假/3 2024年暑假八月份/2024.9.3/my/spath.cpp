#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10,mod=998244353;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
void add_edge(int u,int v){add(u,v),add(v,u);}
struct node2 {
	int a,b,c,d;
}query[N];
int Maxx=0,Maxy=0;
int f(int x,int y,int id) {
	return ((x-1)*Maxy+y-1)*4+id;
}
int dis[5][N];
int sum[5][N];
bool vis[5][N];
void calc(int id) {
	memset(dis[id],0x3f,sizeof dis[id]);
	queue<int>q;
	q.push(f(1,1,id));
	dis[id][f(1,1,id)]=0;
	sum[id][f(1,1,id)]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		if(vis[id][u])continue;
		vis[id][u]=true;
		for(int i=first[u];i;i=a[i].nex) {
			int v=a[i].v;
			if(dis[id][v]>dis[id][u]+1) {
				dis[id][v]=dis[id][u]+1;
				sum[id][v]=sum[id][u];
				q.push(v);
			}
			else if(dis[id][v]==dis[id][u]+1)sum[id][v]=(sum[id][v]+sum[id][u])%mod;
		}
	}
}
signed main() {
	freopen("spath.in","r",stdin);
	freopen("spath.out","w",stdout);
	int q;
	cin>>q;
	for(int i=1;i<=q;i++) {
		cin>>query[i].a>>query[i].b>>query[i].c>>query[i].d;
		query[i].a++,query[i].b++;
		query[i].c++,query[i].d++;
		Maxx=max(Maxx,query[i].a);
		Maxy=max(Maxy,query[i].b);
	}
	for(int i=1;i<=Maxx;i++) {
		for(int j=1;j<=Maxy;j++) {
			add_edge(f(i,j,1),f(i,j,2));
			add_edge(f(i,j,2),f(i,j,3));
			add_edge(f(i,j,3),f(i,j,4));
			add_edge(f(i,j,4),f(i,j,1));
			if(j+1<=Maxy)add(f(i,j,1),f(i,j+1,3));
			if(i+1<=Maxx)add(f(i,j,2),f(i+1,j,4));
			if(j-1>=1)add(f(i,j,3),f(i,j-1,1));
			if(i-1>=1)add(f(i,j,4),f(i-1,j,2));
		}
	}
	calc(1),calc(2),calc(3),calc(4);
	for(int i=1;i<=q;i++) {
		cout<<dis[query[i].c][f(query[i].a,query[i].b,query[i].d)]<<" "<<sum[query[i].c][f(query[i].a,query[i].b,query[i].d)]<<"\n";
	}
}