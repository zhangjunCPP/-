#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dfn[N],low[N],tot;
bool cut[N];
void Tarjan(int u,int edge){
	dfn[u]=low[u]=++tot;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!dfn[v]){
			Tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])cut[i]=cut[i^1]=true;
		}
		else if(i!=(edge^1))low[u]=min(low[u],dfn[v]);
	}
}
int col[N],ecc;
void dfs(int u){
	col[u]=ecc;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(cut[i]||col[v])continue;
		dfs(v);
	}
}
int u[N],v[N];
int deg[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	for(int i=1;i<=n;i++)if(!col[i]){ecc++;dfs(i);}
	for(int i=1;i<=m;i++){
		if(col[u[i]]!=col[v[i]]){
			deg[col[u[i]]]++;
			deg[col[v[i]]]++;
		}
	}
	int ans=0;
	for(int i=1;i<=ecc;i++)if(deg[i]==1)ans++;
	cout<<(ans+1)/2;
}