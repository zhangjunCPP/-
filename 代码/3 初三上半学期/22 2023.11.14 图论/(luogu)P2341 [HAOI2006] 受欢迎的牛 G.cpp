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
int dfn[N],low[N],tot;
bool vis[N];
stack<int>s;
int col[N],scc;
void Tarjan(int u) {
	dfn[u]=low[u]=++tot;
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
		++scc;
		while(s.top()!=u) {
			col[s.top()]=scc;
			vis[s.top()]=false;
			s.pop();
		}
		col[s.top()]=scc;
		vis[s.top()]=false;
		s.pop();
	}
}
int u[N],v[N];
int sum[N];
int du[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++) sum[col[i]]++;
	for(int i=1;i<=m;i++) {if(col[u[i]]!=col[v[i]]) du[col[u[i]]]++;}
	int ans=0,tmp=0;
	for(int i=1;i<=scc;i++) {if(!du[i])tmp++,ans=sum[i];}
	if(tmp==1) cout<<ans;
	else cout<<"0";
	return 0;
}
