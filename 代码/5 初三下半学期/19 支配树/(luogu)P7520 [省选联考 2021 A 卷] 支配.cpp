#include <bits/stdc++.h>

using namespace std;
const int N=3e3+10;
int n,m,q;
int s[N*10],t[N*10];
struct node{
	int v,nex;
}a[N*10];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis1[N][N],vis2[N][N];
void dfs(int u,int opt,int del,bool vis[N][N]){
	if(u==del)return;
	vis[u][opt]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(vis[v][opt])continue;
		dfs(v,opt,del,vis);
	}
}
vector<int>ctrl[N];
int fa[N];
void build(){
	dfs(1,0,0,vis1);
	for(int i=1;i<=n;i++){
		dfs(1,i,i,vis1);
		vis1[i][i]=true;
		for(int j=1;j<=n;j++)if(vis1[j][0]&&!vis1[j][i])ctrl[j].push_back(i);
	}
	for(int i=1;i<=n;i++)for(int j:ctrl[i])if(ctrl[j].size()==ctrl[i].size()-1){fa[i]=j;break;}
}
void clear(){
	memset(first,0,sizeof first);
	cnt=0;
}
int id[N];
bool cmp(int x,int y){return ctrl[x].size()<ctrl[y].size();}
bool flag[N];
void calc(){
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=m;i++)add(t[i],s[i]);
	for(int i=2;i<=n;i++)dfs(i,i,fa[i],vis2);
	for(int i=1;i<=q;i++){
		int ans=0;
		int u,v;
		cin>>u>>v;
		for(int j=1;j<=n;j++)if(vis1[u][fa[j]]&&vis2[v][j]&&fa[j]!=1&&fa[j]!=u)flag[j]=true;
		for(int j=1;j<=n;j++)if(flag[fa[id[j]]])flag[id[j]]=true;
		for(int j=1;j<=n;j++)if(flag[j])ans++;
		memset(flag,0,sizeof flag);
		cout<<ans<<"\n";
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>s[i]>>t[i];
		add(s[i],t[i]);
	}
	build();
	clear();
	calc();
}