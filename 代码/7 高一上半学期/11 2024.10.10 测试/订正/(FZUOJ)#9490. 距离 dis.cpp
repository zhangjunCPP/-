#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int INF=1e9;
int n,m;
	
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int ans[N];
stack<int> sta;
bool vis[N];
vector<int> G;
bool find(int u,int fa){
	sta.push(u);
	vis[u]=true;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		if(vis[v]){
			while(sta.top()!=v){
				vis[sta.top()]=false;
				G.push_back(sta.top());
				sta.pop();
			}
			vis[v]=false;
			G.push_back(v);
			sta.pop();
			return true;
		}
		if(find(v,u))return true;
	}
	sta.pop();
	vis[u]=false;
	return false;
}
int Max[2][N];
void dfs1(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa||vis[v])continue;
		dfs1(v,u);
		if(Max[0][v]+1>Max[0][u])Max[1][u]=Max[0][u],Max[0][u]=Max[0][v]+1;
		else if(Max[0][v]+1>Max[1][u])Max[1][u]=Max[0][v]+1;
	}
}
void dfs2(int u,int fa,int val){
	ans[u]=max(ans[u],val+Max[0][u]);
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa||vis[v])continue;
		dfs2(v,u,max(val,(Max[0][v]+1==Max[0][u]?Max[1][u]:Max[0][u]))+1);
	}
}
void solve1(){
	dfs1(1,0);
	for(int i=1;i<=n;i++)ans[i]=Max[0][i]+Max[1][i];
	dfs2(1,0,0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
int pre[3][N],suf[3][N];
int w[N];
void solve2(){
	find(1,0);
	for(int i=1;i<=n;i++)vis[i]=false;
	for(int it:G)vis[it]=true;
	for(int it:G)dfs1(it,0);
	for(int i=1;i<=n;i++)ans[i]=Max[0][i]+Max[1][i];
	int siz=G.size();
	for(int i=0;i<siz;i++){
		int u=G[i];
		pre[0][i]=suf[0][i]=Max[0][u]-i;
		pre[1][i]=suf[1][i]=Max[0][u]+i;
	}
	for(int i=1;i<siz;i++) pre[0][i]=max(pre[0][i],pre[0][i-1]),pre[1][i]=max(pre[1][i],pre[1][i-1]);
	for(int i=siz-2;i>=0;i--) suf[0][i]=max(suf[0][i+1],suf[0][i]),suf[1][i]=max(suf[1][i+1],suf[1][i]);
	pre[2][0]=-INF,suf[2][siz-1]=-INF;
	for(int i=1;i<siz;i++){
		int u=G[i];
		pre[2][i]=max(pre[2][i-1],Max[0][u]-i+pre[1][i-1]);
	}
	for(int i=siz-2;i>=0;i--){
		int u=G[i];
		suf[2][i]=max(suf[2][i+1],Max[0][u]+i+suf[0][i+1]);
	}
	for(int i=0;i<siz;i++){
		int u=G[i];
		if(i)ans[u]=max(ans[u],pre[0][i-1]+suf[1][i]),w[u]=max(w[u],max(pre[0][i-1]+i,pre[1][i-1]+siz-i));
		if(i!=siz-1)ans[u]=max(ans[u],pre[0][i]+suf[1][i+1]),w[u]=max(w[u],max(suf[1][i+1]-i,suf[0][i+1]+siz+i));
		ans[u]=max(ans[u],pre[2][i]+siz),ans[u]=max(ans[u],suf[2][i]+siz);    
	}
	for(int i=0;i<siz;i++){
		int u=G[i];
		if(i) ans[u]=max(ans[u],pre[0][i-1]+suf[1][i]),w[u]=max(w[u],max(i+pre[0][i-1],-i+pre[1][i-1]+siz));
		if(i!=siz-1) ans[u]=max(ans[u],pre[0][i]+suf[1][i+1]),w[u]=max(w[u],max(-i+suf[1][i+1],i+suf[0][i+1]+siz));
		ans[u]=max(ans[u],pre[2][i]+siz),ans[u]=max(ans[u],suf[2][i]+siz);    
	}
	for(int it:G)dfs2(it,0,w[it]);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	if(m==n-1)solve1();
	else solve2();
}