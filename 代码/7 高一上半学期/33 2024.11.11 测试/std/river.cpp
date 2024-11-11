#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=1e5+10,M=2e5+10,V=N+M,Inf=2e9+10;
int n,m,k;
vector<tuple<int,int,int,int>>a[N];
vector<tuple<int,int,int>>b[N];
vector<pair<int,int>>to[V];
void add(int u,int v,int w){
	to[u].push_back({v,w}),to[v].push_back({u,w});
}
const ll INF=1e18;
ll f[V],g[V],ans[M];
void dij(int s,ll *dis){
	fill(dis+1,dis+1+k,INF);
	dis[s]=0;
	priority_queue<pair<ll,int>>q;
	q.push({0,s});
	static int vis[V];
	fill(vis,vis+1+k,0);
	for(int u;!q.empty();){
		u=q.top().second,q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto [v,w]:to[u]){
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w,q.push({-dis[v],v});
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int x,l,r,v,i=1;i<=m;i++){
		scanf("%d%d%d%d",&x,&l,&r,&v);
		a[x].push_back({l,r,v,i});
	}
	for(int i=1;i<=n;i++){
		sort(all(a[i]));
		b[i].push_back({0,0,++k});
		for(auto [l,r,v,id]:a[i]){
			get<1>(b[i].back())=l;
			add(get<2>(b[i].back()),++k,v);
			b[i].push_back({r+1,0,k});
		}
		get<1>(b[i].back())=Inf;
	}
	for(int i=1;i<n;i++){
		int x=0,y=0;
		for(;x<b[i].size()&&y<b[i+1].size();){
			auto [l1,r1,i1]=b[i][x];
			auto [l2,r2,i2]=b[i+1][y];
			if(max(l1,l2)<=min(r1,r2))add(i1,i2,0);
			if(r1<r2)x++;
			else y++;
		}
	}
	int s=get<2>(b[1][0]),t=get<2>(b[1].back());
	dij(s,f),dij(t,g);
	for(int i=1;i<=n;i++){
		for(int j=0;j<a[i].size();j++){
			int u=get<2>(b[i][j]),v=get<2>(b[i][j+1]);
			int w=get<2>(a[i][j]),id=get<3>(a[i][j]);
			ans[id]=min({f[u]+g[v],f[v]+g[u],f[t]});
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif