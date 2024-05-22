#include <bits/stdc++.h>
using namespace std;
const int N=6e5+10;
int n;
struct node{int v,nex;}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	deg[v]++;
}
int dep[N];
int fa[N][20];
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
vector<int>G2[N];
void topsort(){
	queue<int> q;
	for(int i=1;i<=n;i++)fa[i][0]=-1;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i),fa[i][0]=0;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		int dad=fa[now][0];
		G2[dad].emplace_back(now);
		dep[now]=dep[dad]+1;
		for(int i=1;i<20;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
		for(int i=first[now];i;i=a[i].nex){
			int v=a[i].v;
			if(fa[v][0]==-1)fa[v][0]=now;
			else fa[v][0]=LCA(fa[v][0],now);
			deg[v]--;
			if(!deg[v])q.push(v);
		}
	}
}
int siz[N];
void dfs(int u){
	siz[u]=1;
	for(int v:G2[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		int v;
		cin>>v;
		while(v!=0){
			add(v,i);
			cin>>v;
		}
	}
	topsort();
	dfs(0);
	for(int i=1;i<=n;i++)cout<<siz[i]-1<<"\n";
}