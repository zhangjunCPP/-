#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int> G[N];
int depth[N],fa[N][20],siz[N];
void dfs(int u,int dad){
    depth[u]=depth[dad]+1;fa[u][0]=dad;siz[u]=1;
    for(int i=1;i<=17;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int v:G[u]){
        if(v==dad) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
}
int LCA(int x,int y){
    if(depth[x]<depth[y]) swap(x,y);
    for(int i=17;i>=0;i--)if(depth[fa[x][i]]>=depth[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=17;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
bool del[N],vis[N];
int siz2[N];
void dfs2(int u,int dad){
	vis[u]=true;
	siz2[u]=1;
	for(int v:G[u]){
		if(v==dad||del[v])continue;
		dfs2(v,u);
		siz2[u]+=siz2[v];
	}
}
void solve(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)G[i].clear();
	int ans=0;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			int tmp1=i,tmp2=j;
			int lca=LCA(tmp1,tmp2);
			for(int l=1;l<=n;l++)del[l]=false,vis[l]=false,siz2[l]=0;
			while(tmp1!=lca){del[tmp1]=true;tmp1=fa[tmp1][0];}
			while(tmp2!=lca){del[tmp2]=true;tmp2=fa[tmp2][0];}
			del[lca]=true;
			int tmp=0;
			for(int l=1;l<=n;l++){
				if(vis[l]||del[l])continue;
				dfs2(l,0);
				tmp+=siz2[l]>=k;
			}
			ans=max(ans,tmp);
		}
	}
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}

