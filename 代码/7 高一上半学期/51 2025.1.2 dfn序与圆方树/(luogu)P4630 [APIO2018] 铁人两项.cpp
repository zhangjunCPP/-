#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,q;
vector<int> G[N];
int dfn[N],low[N],tot;
stack<int> sta;
int cnt_c;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int val[N];
int all;
void tarjan(int u){
	all++;
	dfn[u]=low[u]=++tot;
	val[u]=-1;
	sta.push(u);
	for(int v:G[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				cnt_c++;
				while(!sta.empty()&&sta.top()!=v){
					add(cnt_c,sta.top());add(sta.top(),cnt_c);
					val[cnt_c]++;
					sta.pop();
				}
				add(cnt_c,v),add(v,cnt_c);
				sta.pop();
				add(cnt_c,u);add(u,cnt_c);
				val[cnt_c]+=2;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}
int ans;
int siz[N];
void dfs(int u,int fa){
	siz[u]=u<=n;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		ans+=2*siz[u]*siz[v]*val[u];
		siz[u]+=siz[v];
	}
	ans+=2*siz[u]*(all-siz[u])*val[u];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cnt_c=n;
	for(int i=1;i<=n;i++)if(!dfn[i]){
		all=0;
		tarjan(i),sta.pop();
		dfs(i,0);
	}
	cout<<ans;
}