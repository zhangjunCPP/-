#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+5;

int fa[maxn], c[maxn], dep[maxn], vis[maxn];
vector<int> g[maxn];

struct node {
	int u;
	int v;
	int c;
}e[maxn];

void dfs(int x,int fx) {
	dep[x]=dep[fx]+1;
	for(int y:g[x]) dfs(y,x);
	return ;
}

int find(int x) {
	if(fa[x]!=x) return fa[x]=find(fa[x]);
	return x;
}

void solve() {
	int n; cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i, c[i]=vis[i]=0, g[i].clear();
	for(int i=1;i<n;i++) {
		cin>>e[i].u>>e[i].v>>e[i].c;
		g[e[i].u].push_back(e[i].v);
		vis[e[i].v]=1;
	}
	int rt=0;
	for(int i=1;i<=n;i++) if(!vis[i]) rt=i;
	dfs(rt,0);
	for(int i=1;i<n;i++) {
		int u=e[i].u,v=e[i].v,C=e[i].c;
		u=find(u), v=find(v);
		fa[v]=u, c[u]=max(c[u],c[v]+dep[e[i].u]-dep[u]+1);
		cout<<c[C]<<' ';
	}
	cout<<'\n';
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
	return 0;
}