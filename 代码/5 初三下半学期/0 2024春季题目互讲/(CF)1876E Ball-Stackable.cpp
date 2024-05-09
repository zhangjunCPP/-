#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int dp[N];
void dfs1(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dp[1]+=(a[i].w!=-1);
		dfs1(v,u);
	}
}
int ans,rt;
void dfs(int u,int fa){
	if(dp[u]>ans)ans=dp[u],rt=u;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dp[v]=dp[u]-a[i].w;
		dfs(v,u);
	}
}
int col;
stack<int> s;
void get_color(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		int tmp;
		if(a[i].w==-1){cout<<v<<" "<<u<<" "<<(tmp=s.top())<<"\n";s.pop();}
		else{col++;cout<<u<<" "<<v<<" "<<col<<"\n";s.push(col);}
		get_color(v,u);
		if(a[i].w==-1)s.push(tmp);
		else s.pop();
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v,u,-w);
	}
	dfs1(1,0);
	dfs(1,0);
	cout<<ans<<"\n";
	get_color(rt,0);
}