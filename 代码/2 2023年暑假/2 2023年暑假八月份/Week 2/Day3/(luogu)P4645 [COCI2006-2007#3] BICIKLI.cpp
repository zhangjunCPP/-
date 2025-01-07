#include <bits/stdc++.h>
const int mod=1e9;
using namespace std;
const int N=200005;

vector<int> G[N];
vector<int> G2[N];
int in[N];

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

bool vis1[N];
void bfs1(){
	queue<int> q;
	q.push(1);
	vis1[1]=true;
	while (!q.empty()){
		int now=q.front();
		q.pop();
		for(int v:G[now]){
			if(!vis1[v]){
				vis1[v]=true;
				q.push(v);
			}
			in[v]++;
		}
	}
}

bool vis2[N];
void bfs2(){
	queue<int> q;
	q.push(2);
	vis2[2]=true;
	while (!q.empty()){
		int now=q.front();
		q.pop();
		for(int v:G2[now]){
			if(!vis2[v]){
				vis2[v]=true;
				q.push(v);
			}
		}
	}
}

int ans[N];
void solve(){
	queue<int> q;
	q.push(1);
	ans[1]=1;
	while (!q.empty()){
		int now=q.front();
		q.pop();
		for(int v:G[now]){
			if(vis1[v]&&vis2[v]){
				ans[v]+=ans[now];
				ans[v]%=mod;
				in[v]--;
				if(in[v]==0) q.push(v);
			}
		}
	}
}

int sum[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G2[v].push_back(u);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	bfs1();
	bfs2();
	for(int i=1;i<=n;i++) sum[scc[i]]++;
	for(int i=1;i<=n;i++) if(vis1[i]&&vis2[i]&&sum[scc[i]]>1) {puts("inf");return 0;}
	solve();
	cout<<ans[2];
}