#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000000;
int m[N];
vector<int> G[N];
priority_queue<int> q[N];
void merge(int x,int y) {
	vector<int> t;
	if(q[x].size()<q[y].size())swap(q[x],q[y]);
	while(q[y].size()) {
		t.push_back(max(q[x].top(),q[y].top()));
		q[x].pop(),q[y].pop();
	}
	for(int i:t)q[x].push(i);
}
void dfs(int u) {
	for(int i:G[u]) {
		dfs(i);
		merge(u,i);
	}
	q[u].push(m[u]);
}
signed main() {
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)cin>>m[i];
	for(int i=2; i<=n; i++) {
		int f;
		cin>>f;
		G[f].push_back(i);
	}
	dfs(1);
	int ans=0;
	while(q[1].size()) {
		ans+=q[1].top();
		q[1].pop();
	}
	cout<<ans;
}