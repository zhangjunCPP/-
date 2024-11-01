#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2000+10;
const ll INF=1e18;
int n,m,q;
struct node{
	int u,v;
	ll l,r,w;
	node(int _u=0,int _v=0,ll _l=0,ll _r=0,ll _w=0):u(_u),v(_v),l(_l),r(_r),w(_w){}
}a[N];
struct node2{
	int v;
	ll l,r,w;
	int nex;
}edge1[N],edge2[N];
int first1[N],cnt1;
void add1(int u,int v,ll l,ll r,ll w){
	edge1[++cnt1]={v,l,r,w,first1[u]};
	first1[u]=cnt1;
}
int first2[N],cnt2;
void add2(int u,int v,ll l,ll r,ll w){
	edge2[++cnt2]={v,l,r,w,first2[u]};
	first2[u]=cnt2;
}
ll dis[2][N][N];
bool vis[N];
void dij1(int s,ll tim,int opt){
	priority_queue<pair<ll,int>>q;
	for(int i=1;i<=n;i++)dis[0][opt][i]=INF,vis[i]=false;
	dis[0][opt][s]=tim;
	q.emplace(-dis[0][opt][s],s);
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first1[u];i;i=edge1[i].nex){
			int v=edge1[i].v;
			ll w=edge1[i].w,l=edge1[i].l,r=edge1[i].r;
			if(dis[0][opt][u]<=r&&dis[0][opt][v]>max(l,dis[0][opt][u])+w){
				dis[0][opt][v]=max(l,dis[0][opt][u])+w;
				q.emplace(-dis[0][opt][v],v);
			}
		}
	}
}
void dij2(int s,ll tim,int opt){
	priority_queue<pair<ll,int>>q;
	for(int i=1;i<=n;i++)dis[1][opt][i]=-INF,vis[i]=false;
	dis[1][opt][s]=tim;
	q.emplace(dis[1][opt][s],s);
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first2[u];i;i=edge2[i].nex){
			int v=edge2[i].v;
			ll w=edge2[i].w,l=edge2[i].l,r=edge2[i].r;
			if(dis[1][opt][u]>=l+w&&dis[1][opt][v]<min(r+w,dis[1][opt][u])-w){
				dis[1][opt][v]=min(r+w,dis[1][opt][u])-w;
				q.emplace(dis[1][opt][v],v);
			}
		}
	}
}
ll ans[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>a[i].u>>a[i].v>>a[i].l>>a[i].r>>a[i].w;
		a[i].r-=a[i].w;
		if(a[i].l<=a[i].r){
			add1(a[i].u,a[i].v,a[i].l,a[i].r,a[i].w);
			add2(a[i].v,a[i].u,a[i].l,a[i].r,a[i].w);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)ans[i][j]=INF;
		ans[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		dij1(a[i].v,a[i].r+a[i].w,i);
		dij2(a[i].u,a[i].r,i);
		vector<int> tmp1,tmp2;
		for(int j=1;j<=n;j++)if(dis[1][i][j]>=0)tmp1.push_back(j);
		for(int j=1;j<=n;j++)if(dis[0][i][j]<INF)tmp2.push_back(j);
		for(int u:tmp1)for(int v:tmp2)ans[u][v]=min(ans[u][v],dis[0][i][v]-dis[1][i][u]);
	}
	while(q--){
		int s,t;
		cin>>s>>t;
		if(ans[s][t]==INF)cout<<"-1\n";
		else cout<<ans[s][t]<<"\n";
	}
}