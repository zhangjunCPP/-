#include <bits/stdc++.h>
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
int dfn[N],low[N],idx;
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	s.push(u);
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}

	if(low[u]==dfn[u]){
		++tot;
		while (s.top()!=u){
			scc[s.top()]=tot;
			vis[s.top()]=false;
			s.pop();
		}
		scc[s.top()]=tot;
		vis[s.top()]=false;
		s.pop();
	}
}
int u[N],v[N];
int ru[N];
int money[N];
int cost[N];
int main(){
	int n,p;
	cin>>n>>p;
	for(int i=1;i<=n;i++) money[i]=0x3f3f3f3f,cost[i]=0x3f3f3f3f;
	for(int i=1;i<=p;i++) {
		int id,val;
		cin>>id>>val;
		money[id]=val;
	}
	int r;
	cin>>r;
	for(int i=1;i<=r;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
	}
	for(int i=1;i<=n;i++) {
		if (!dfn[i] && money[i] != 0x3f3f3f3f) {
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]){puts("NO");cout<<i; return 0;}
	puts("YES");
	for(int i=1;i<=r;i++)if(scc[u[i]]!=scc[v[i]]) ru[scc[v[i]]]++;
	for(int i=1;i<=n;i++){if(money[i]!=0x3f3f3f3f)cost[scc[i]]=min(cost[scc[i]],money[i]);}
	int ans=0;
	for(int i=1;i<=tot;i++) if(!ru[i]) ans+=cost[i];
	cout<<ans;
}