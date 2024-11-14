#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis[N];
int ans;
void dfs(int u,int sum){
	ans=max(ans,sum);
	vis[u]=true;
	vector<int>tmp;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!vis[v])tmp.push_back(v);
	}
	for(int i=first[u];i;i=a[i].nex)vis[a[i].v]=true;
	for(int v:tmp)dfs(v,sum+1);
}
int main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)vis[j]=false;
		dfs(i,1);
	}
	cout<<ans;
}