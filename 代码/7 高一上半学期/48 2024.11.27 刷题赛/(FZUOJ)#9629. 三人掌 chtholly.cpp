#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int n,m,q;
vector<int> G[N];
int dfn[N],low[N],tot;
stack<int> sta;
int cnt_c;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	deg[v]++;
}
void tarjan(int u){
	dfn[u]=low[u]=++tot;
	sta.push(u);
	for(int v:G[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u]){
				cnt_c++;
				while(!sta.empty()&&sta.top()!=v){
					add(cnt_c,sta.top());
					add(sta.top(),cnt_c);
					sta.pop();
				}
				add(cnt_c,v),add(v,cnt_c);
				sta.pop();
				add(cnt_c,u);
				add(u,cnt_c);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}
int fa[N][20],dep[N];
int val1[N],val2[N];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	val1[u]=val1[dad]+(u>n);
	val2[u]=val2[dad]+(u>n&&deg[u]==2);
	fa[u][0]=dad;
	for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	cin>>n>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cnt_c=n;
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i),sta.pop();
	dfs(1,0);
	while(q--){
		int x,y,k;
		cin>>x>>y>>k;
		int LCA=lca(x,y);
		int dis=dep[x]+dep[y]-2*dep[LCA];
		int p=val1[x]+val1[y]-2*val1[LCA]+(LCA>n);
		dis-=p;
		p-=val2[x]+val2[y]-2*val2[LCA]+(LCA>n&&deg[LCA]==2);
		if(k<dis)cout<<"0\n";
		else cout<<C(p,k-dis)<<"\n";
	}
}