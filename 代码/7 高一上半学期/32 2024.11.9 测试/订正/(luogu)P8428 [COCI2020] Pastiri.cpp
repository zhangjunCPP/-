#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N],fa[N];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
	}
}
queue<int> q;
bool vis[N];
int dis[N];
void spfa(){
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!vis[v])q.push(v),vis[v]=true;
			}
		}
	}
}
void dfs2(int u,int tot){
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(vis[v]||dis[v]!=tot-1)continue;
		dfs2(v,tot-1);
	}
}
int id[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=k;i++){
		cin>>id[i];
		dis[id[i]]=0;
		q.push(id[i]);
		vis[id[i]]=true;
	}
	spfa();
	memset(vis,false,sizeof vis);
	sort(id+1,id+k+1,[](const int&x,const int&y){return dep[x]>dep[y];});
	vector<int>ans;
	for(int i=1;i<=k;i++){
		if(vis[id[i]])continue;
		int tmp=id[i];
		while(fa[tmp]&&dis[fa[tmp]]==dis[tmp]+1)tmp=fa[tmp];
		dfs2(tmp,dep[id[i]]-dep[tmp]);
		ans.push_back(tmp);
	}
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<" ";
}