#include <bits/stdc++.h>
using namespace std;
const int N=200005;
vector<int> G[N];
int dfn[N],low[N],idx;
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	s.push(u);
	vis[u]=true;
	for(int v:G[u]){
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
int ru[N];
int u[N],v[N],w[N];
int n,m;
bool check(int mid){
	for(int i=1;i<=n;i++) dfn[i]=low[i]=vis[i]=scc[i]=ru[i]=0;
	while(!s.empty()) s.pop();
	tot=idx=0;
	for(int i=1;i<=n;i++) G[i].clear();

	for(int i=1;i<=m;i++){
		G[u[i]].push_back(v[i]);
		if(w[i]>mid) continue;
		G[v[i]].push_back(u[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int u=1;u<=n;u++){
		for(int v:G[u]){
			if(scc[u]!=scc[v]) ru[scc[v]]++;
		}
	}
	int tmp=0;
	for(int i=1;i<=tot;i++) if(ru[i]==0) tmp++;
	return tmp==1;
}
void solve(){
	cin>>n>>m;
	int MAX=-1;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		MAX=max(MAX,w[i]);
	}

	int l=0,r=MAX+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	if(l>MAX) cout<<"-1\n";
	else cout<<l<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}