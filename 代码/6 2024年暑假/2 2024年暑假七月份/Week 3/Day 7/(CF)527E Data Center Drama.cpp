#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node {
	int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int deg[N];
vector<int>G;
bool vis[N];
bool opt;
void dfs(int u) {
	for(int i=first[u];i;i=first[u]){
		first[u]=a[i].nex;
		if(vis[i])continue;
		vis[i]=vis[i^1]=true;
		int v=a[i].v;
		dfs(v);
		if(opt)cout<<u<<" "<<v<<"\n";
		else cout<<v<<" "<<u<<"\n";
		opt^=1;
	}
}
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)if(deg[i]&1)G.push_back(i);
	for(int i=0;i<G.size();i+=2)add(G[i],G[i+1]),add(G[i+1],G[i]),m++;
	if(m&1)add(1,1),add(1,1),m++;
	cout<<m<<"\n";
	dfs(1);
}