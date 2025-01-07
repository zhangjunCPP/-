#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int to[N][30];
void update(int u,int v){
	to[u][0]=v;
	for(int i=1;i<=25;i++) to[u][i]=to[to[u][i-1]][i-1];
}
int siz[N];
void dfs(int u,int dad){
	siz[u]=1;
	int son=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son]) son=v;
	}
	update(u,son);
}
int calc(int u){
	int v=u;
	for(int i=25;i>=0;i--)if(siz[to[v][i]]*2>=siz[u]) v=to[v][i];
	return v;
}
int ans[N];
void dfs2(int u,int dad){
	int son1=0,son2=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(siz[v]>siz[son1]) son2=son1,son1=v;
		else if(siz[v]>siz[son2]) son2=v;
	}
	int tmp=to[u][0];

	update(u,son1);
	ans[u]=calc(son1);
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad||v==son1) continue;
		siz[u]-=siz[v];
		siz[v]+=siz[u];
		dfs2(v,u);
		siz[v]-=siz[u];
		siz[u]+=siz[v];
	}
	if(son1&&son1!=dad){
		update(u,son2);
		siz[u]-=siz[son1];
		siz[son1]+=siz[u];
		dfs2(son1,u);
		siz[son1]-=siz[u];
		siz[u]+=siz[son1];
	}
	update(u,tmp);

}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
}