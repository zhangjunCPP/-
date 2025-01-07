#include<bits/stdc++.h>
#define ll long long
using namespace std;
vector<pair<ll,int> > G[40000010];
int tree[2][40000010][2],tot1,tot2;
int sum[40000010];
int insert(ll x,int opt,int w,int &tot) {
	int now=0;
	while(x>1){
		if(!tree[opt][now][x&1]) tree[opt][now][x&1]=++tot;
		now=tree[opt][now][x&1];
		x>>=1;
	}
	sum[now]+=w;
	return now;
}
int ask(ll x){
	int now=0;
	int num=sum[0];
	while(x>1&&tree[1][now][x&1]){
		now=tree[1][now][x&1];
		num+=sum[now];
		x>>=1;
	}
	return num;
}
int ans[400010];
void dfs(int u){
	for(auto v:G[u]){
		if(v.first<0) insert(-v.first,1,v.second,tot2);
		else ans[v.second]=ask(v.first);
	}
	if(tree[0][u][0]) dfs(tree[0][u][0]);
	if(tree[0][u][1]) dfs(tree[0][u][1]);
	for(auto v:G[u]) if(v.first<0) insert(-v.first,1,-v.second,tot2);
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,m;
	cin>>n>>n>>m;
	for(int i=1;i<=n;i++){
		ll x,y,w;
		cin>>x>>y>>w;
		G[insert(x,0,0,tot1)].push_back({-y,w});
	}
	for(int i=1;i<=m;i++){
		ll x,y;
		cin>>x>>y;
		G[insert(x,0,0,tot1)].push_back({y,i});
	}
	dfs(0);
	for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
}