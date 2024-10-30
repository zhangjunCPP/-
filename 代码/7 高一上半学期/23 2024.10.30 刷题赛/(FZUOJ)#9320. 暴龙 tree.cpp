#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int fa[N][20];
int dep[N];
int dis[N];
void dfs(int u,int dad){
	fa[u][0]=dad;
	dep[u]=dep[dad]+1;
	for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dis[v]=dis[u]+a[i].w;
		dfs(v,u);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int Dis(int x,int y){return dis[x]+dis[y]-2*dis[LCA(x,y)];}
int p[N];
pair<int,int> Min[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=k;i++)Min[i].first=Min[i].second=-1;
	for(int i=1;i<=n;i++){
		if(Min[p[i]].first==-1)Min[p[i]].first=Min[p[i]].second=i;
		else{
			int dis1=Dis(i,Min[p[i]].first);
			int dis2=Dis(i,Min[p[i]].second);
			int dis3=Dis(Min[p[i]].first,Min[p[i]].second);
			if(dis1>=dis2&&dis1>dis3)Min[p[i]].second=i;
			else if(dis2>=dis1&&dis2>dis3)Min[p[i]].first=i;
		}
	}
	for(int i=1;i<=k;i++){
		if(Min[i].first==-1)cout<<"0\n";
		else cout<<Dis(Min[i].first,Min[i].second)<<"\n";
	}
}