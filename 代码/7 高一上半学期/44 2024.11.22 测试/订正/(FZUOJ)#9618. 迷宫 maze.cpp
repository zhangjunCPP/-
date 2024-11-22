#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int fa[N],dep[N];
int son[N];
int ans[N];
void dfs1(int u,int dad,int mx1,int mx2){
	fa[u]=dad;
	dep[u]=dep[dad]+1;
	if(u>mx1)mx2=mx1,mx1=u;
	else if(u>mx2)mx2=u;
	if(u!=1)ans[dep[mx2]<dep[mx1]?mx1:son[mx1]]++;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		son[u]=v;
		dfs1(v,u,mx1,mx2);
	}
}
void dfs2(int u,int dad){
	ans[u]+=ans[dad];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs2(v,u);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs1(1,0,0,0);
	dfs2(1,0);
	for(int i=2;i<=n;i++)cout<<ans[i]<<" ";
}