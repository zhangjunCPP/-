#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N];
int fa[N][25];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fa[u][0]=dad;
	for(int i=1;i<25;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=24;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	}
	if(x==y) return x;
	for(int i=24;i>=0;i--){
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}



int diff[N];
void solve(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		solve(v,u);
		diff[u]+=diff[v];
	}
}
int s[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	for(int i=2;i<=n;i++){
		int x=s[i-1],y=s[i];
		int LCA=lca(x,y);
		diff[x]++,diff[y]++;
		diff[LCA]--,diff[fa[LCA][0]]--;
	}
	solve(1,0);
	for(int i=2;i<=n;i++) diff[s[i]]--;
	for(int i=1;i<=n;i++) cout<<diff[i]<<"\n";
	return 0;

}