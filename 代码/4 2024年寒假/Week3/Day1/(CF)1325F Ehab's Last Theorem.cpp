#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int n,m,k;
int dep[N];
int fa[N];
bool vis[N];
void solve2(int u,int v){
	cout<<"2\n";
	cout<<dep[u]-dep[v]+1<<"\n";
	while(u!=v){
		cout<<u<<" ";
		u=fa[u];
	}
	cout<<v;
	exit(0);
}
vector<int> ans;
bool flag[N];
void dfs(int u,int dad){
	fa[u]=dad;
	dep[u]=dep[dad]+1;
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		if(vis[v]){
			if(dep[u]<dep[v])continue;
			if(dep[u]-dep[v]+1>=k) solve2(u,v);
			continue;
		}
		dfs(v,u);
	}
	if(!flag[u]){
		ans.push_back(u);
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			flag[v]=true;
		}
		flag[u]=true;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	k=ceil(sqrt(n));
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<"1\n";
	for(int i=0;i<k;i++)cout<<ans[i]<<" ";
}