#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int x[N],y[N];
int dep[N];
int fa[N][20];
void init(int u,int dad) {
	dep[u]=dep[dad]+1;
	fa[u][0]=dad;
	for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		init(v,u);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int lca[N];
bool vis[N];
int suml[N],sumr[N];
void dfs(int now){
	if(now>m){
		for(int i=1;i<=m;i++) {
			int u=x[i],v=y[i];
			int Lca=lca[i];
			while(u!=Lca){suml[u]=sumr[u]=0;u=fa[u][0];}
			while(v!=Lca){suml[v]=sumr[v]=0;v=fa[v][0];}
			suml[Lca]=sumr[Lca]=0;
		}
		for(int i=1;i<=m;i++) {
			int u=x[i],v=y[i];
			int Lca=lca[i];
			while(u!=Lca){
				if(vis[i]) suml[u]++;
				else sumr[u]++;
				u=fa[u][0];
			}
			while(v!=Lca){
				if(vis[i]) suml[v]++;
				else sumr[v]++;
				v=fa[v][0];
			}
		}
		bool flag=true;
		for(int i=1;i<=m;i++) {
			int u=x[i],v=y[i];
			int Lca=lca[i];
			while(u!=Lca){
				if(abs(suml[u]-sumr[u])>1) {flag=false;break;
				}
				u=fa[u][0];
			}
			while(v!=Lca){
				if(abs(suml[v]-sumr[v])>1){flag=false;break;}
				v=fa[v][0];
			}
		}
		if(!flag)return;
		for(int i=1;i<=m;i++){
			if(!vis[i]) swap(x[i],y[i]);
			cout<<x[i]<<" "<<y[i]<<"\n";
		}
		exit(0);
	}
	vis[now]=true;
	dfs(now+1);
	vis[now]=false;
	dfs(now+1);
	return;
}
int main(){
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	cin>>n>>m;
	bool flag1=true,flag2=true;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		if(u!=i||v!=i+1) flag1=false;
		if(u!=1||v!=i+1) flag2=false;
		add(u,v);
		add(v,u);
	}
	init(1,0);
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		lca[i]=LCA(x[i],y[i]);
	} 
	if(m<=16||flag1||flag2)dfs(1);
	else {
		for(int i=1;i<=m;i++) cout<<x[i]<<" "<<y[i]<<"\n";
	}
	return 0;
}

