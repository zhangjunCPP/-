#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int deg[N][2];
bool vis[N][2];
void dfs(int u,int opt) {
	vis[u][opt]=true;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		deg[v][opt^1]--;
		if(opt&&!deg[v][0])dfs(v,0);
		if(!opt&&!vis[v][1])dfs(v,1);
	}
}
bool tmp[N][2];
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(v,u);
		deg[u][0]++,deg[u][1]++;
	}
	for(int i=1;i<=n;i++)if(!deg[i][0]&&!vis[i][0])dfs(i,0);
	memcpy(tmp,vis,sizeof tmp);
	for(int i=1;i<=n;i++)if(!deg[i][1]&&!vis[i][1])dfs(i,1);
	for(int j=0;j<2;j++) {
		for(int i=1;i<=n;i++) {
			if(!vis[i][j])cout<<"D";
			else if(tmp[i][j]==j)cout<<"W";
			else cout<<"L";
		}
		cout<<"\n";
	}
}