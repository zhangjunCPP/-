#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=42;
int n,m,ans,vis[N];
vector<int>to[N];
void dfs(int u,int d){
	ans=max(ans,d);
	for(int v:to[u])vis[v]++;
	for(int v:to[u])if(vis[v]==1)dfs(v,d+1);
	for(int v:to[u])vis[v]--;
}
int main(){
	cin>>n>>m;
	for(int u,v;m--;){
		cin>>u>>v;
		to[u].push_back(v),to[v].push_back(u);
	}
	for(int i=1;i<=n;i++)vis[i]++,dfs(i,1),vis[i]--;
	cout<<ans<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif