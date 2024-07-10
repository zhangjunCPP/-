#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<int> G[N];
int a[N],b[N];
int col[N];
bool vis[N];
void dfs(int u,int color) {
	col[u]=color;
	vis[u]=true;
	for(int v:G[u])if(!vis[v])dfs(v,3-color);
}
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i]>>b[i];
		G[a[i]].push_back(b[i]);
		G[b[i]].push_back(a[i]);
	}
	for(int i=1;i<=n;i++) {
		G[2*i].push_back(2*i-1);
		G[2*i-1].push_back(2*i);
	}
	for(int i=1;i<=2*n;i++)if(!vis[i])dfs(i,1);
	for(int i=1;i<=n;i++)cout<<col[a[i]]<<" "<<col[b[i]]<<"\n";
}