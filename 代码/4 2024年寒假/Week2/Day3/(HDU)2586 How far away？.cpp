#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct Node{
    int v,w,nex;
} a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
vector<pair<int,int> > G[N];
int dis[N];
void dfs(int u){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dis[v]){
            dis[v]=dis[u]+a[i].w;
            dfs(v);
        }
    }
}
int fa[N];
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
int ans[N];
int vis[N];
void Tarjan(int u){
    vis[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!vis[v]){
            Tarjan(v);
            fa[v]=u;
        }
    }
    for(auto i: G[u]){
        int v=i.first,id=i.second;
        if(vis[v]==2){
            int lca=find(v);
            ans[id]=dis[u]+dis[v]-2*dis[lca];
        }
    }
    vis[u]=2;
}
int n,q;
void init(){
    cnt=0;
    memset(first,0,sizeof first);
    memset(dis,0,sizeof dis);
    dis[1]=1;
    for(int i=1;i<=n;i++)fa[i]=i;
    memset(vis,0,sizeof vis);
}
void solve(){
    cin>>n>>q;
    init();
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1);
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back({v,i});
        G[v].push_back({u,i});
    }
    Tarjan(1);
    for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
}
int main(){
    int t;
    cin>>t;
    while(t--) solve();
}