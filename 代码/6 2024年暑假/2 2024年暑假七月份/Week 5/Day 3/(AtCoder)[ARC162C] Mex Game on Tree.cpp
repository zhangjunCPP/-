#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,k;
vector<int>G[N];
int a[N];

bitset<N>son[N];
int sum[N];
bool ans;
void dfs(int u) {
	if(ans)return;
	if(a[u]!=-1)son[u][a[u]]=false;
	else sum[u]++;
	for(auto v:G[u]) {
		dfs(v);
		sum[u]+=sum[v];
		son[u]&=son[v];
	}
	if(sum[u]<=1){
		ans|=(son[u]._Find_first()==k);
		if(sum[u])ans|=(son[u]._Find_next(son[u]._Find_first())==k);
	}
}
void solve(){
	ans=false;
	memset(sum,0,sizeof sum);
	cin>>n>>k;
	for(int i=1;i<=n;i++)son[i].set();
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		G[fa].push_back(i);
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1);
	if(ans)puts("Alice");
	else puts("Bob");
}
signed main() {
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}