#include <bits/stdc++.h>

using namespace std;
const int N=4005;

bitset<N> dp[N];
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
			dp[tot][s.top()]=1;
			s.pop();
		}
		scc[s.top()]=tot;
		vis[s.top()]=false;
		dp[tot][s.top()]=1;
		s.pop();
	}
}
int x[N],d[N];
map<pair<int,int>,bool> mp;
vector<int> G2[N];
int in[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>d[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) {
			if(i==j) continue;
			if(abs(x[i]-x[j])<=d[i]) G[i].push_back(j);
		}
	}
	for(int i=1;i<=n;i++)if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++){
		for(int j:G[i]){
			if(scc[i]==scc[j]||mp[make_pair(scc[i],scc[j])]) continue;
			mp[make_pair(scc[i],scc[j])]=true;
			G2[scc[i]].push_back(scc[j]);
			in[scc[j]]++;
		}
	}

	queue<int> q;
	for(int i=1;i<=tot;i++){
		if(in[i]==0) q.push(i);
	}
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int v:G2[now]){
			dp[v]|=dp[now];
			in[v]--;
			if(in[v]==0) q.push(v);
		}
	}
	double ans=0;
	for(int i=1;i<=n;i++) ans+=1.0/(dp[scc[i]].count());
	printf("%.4lf",ans);
}