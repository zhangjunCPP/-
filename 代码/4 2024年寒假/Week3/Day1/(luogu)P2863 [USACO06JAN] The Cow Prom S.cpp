#include<bits/stdc++.h>
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
int dfn[N],tot;
int low[N];
int scc[N],col;
stack<int>s;
bool vis[N];
void Tarjan(int u){
	low[u]=dfn[u]=++tot;
	s.push(u);
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		scc[u]=++col;
		while(s.top()!=u){
			scc[s.top()]=col;
			vis[s.top()]=false;
			s.pop();
		}
		s.pop();
		vis[u]=false;
	}
}
int num[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	for(int i=1;i<=n;i++)num[scc[i]]++;
	int ans=0;
	for(int i=1;i<=col;i++)if(num[i]>1)ans++;
	cout<<ans;
}