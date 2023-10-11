#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,m;
vector<int> G[N];
int d[N];
int ans[N];
int dis[N];
bool vis[N];

int pre[N],nex[N]; 
void del(int x) {
	nex[pre[x]]=nex[x];
	pre[nex[x]]=pre[x];
}
void bfs(int s) {
	for(int i=1;i<=n;i++) dis[i]=1e9;
	for(int i=1;i<=n;i++) pre[i]=i-1,nex[i]=i+1;
	nex[0]=1,pre[n+1]=n;
	dis[s]=0;
	queue<int> q;
	q.push(s);
	del(s);
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		for(int i:G[now]) vis[i]=true;
		for(int i=nex[0];i<=n;i=nex[i]) {
			if(vis[i]) continue;
			dis[i]=dis[now]+1;
			q.push(i);
			del(i);
		}
		for(int i:G[now]) vis[i]=false;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v),d[u]++;
		G[v].push_back(u),d[v]++;
	}
	int sum=0;
	for(int i=1;i<=n;i++) {
		if(d[i]*2>=n) {
			bfs(i);
			for(int j=1;j<=n;j++) if(dis[j]<=n&&(j<i||d[j]*2<n)) ans[dis[j]]++;
		}
		else {
			ans[1]+=sum;
			sum++;
			for(int j:G[i]) if(j<i&&d[j]*2<n)ans[1]--,ans[2]++;
		}
	}
	for(int i=1;i<n;i++) cout<<ans[i]<<" ";
	return 0;
}
