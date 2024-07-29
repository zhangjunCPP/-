#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int INF=1e18;
vector<int>G1[N],G2[N];
int dis1[N],dis2[N];
bool vis[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,A,B;
	cin>>n>>m>>A>>B;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		G1[u].push_back(v);G1[v].push_back(u);
		G2[u].push_back(v);G2[v].push_back(u);
	}
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int v:G1[u])if(!dis1[v])dis1[v]=dis1[u]+1,q.push(v);
	}
	for(int i=1;i<=n;i++)dis2[i]=INF;
	dis2[1]=0;
	q.push(1);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int v:G1[u])vis[v]=true;
		for(int v:G1[u]) {
			for(auto k=G2[v].begin();k!=G2[v].end();) {
				int w=*k;
				if(w!=u&&!vis[w]&&dis2[w]>dis2[u]+1)dis2[w]=dis2[u]+1,q.push(w);
				if(!vis[w])k=G2[v].erase(k);
				else ++k;
			}
		}
		for(int v:G1[u])vis[v]=false;
	}
	for(int i=2;i<=n;i++)dis1[i]=min(A*dis1[i],dis1[i]&1?dis1[i]/2*B+A:dis1[i]/2*B);
	for(int i=2;i<=n;i++)cout<<min(dis1[i],(dis2[i]!=INF?dis2[i]*B:INF))<<"\n";
}