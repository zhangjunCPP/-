#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
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
vector<pair<int,int> >G[3];
int col[N];
void dfs(int u,int color){
    col[u]=color;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!col[v])dfs(v,color^1);
        else if(col[u]==col[v]){
            puts("NO");
            exit(0);
        }
    }
}
int vis[N];
void dfs2(int u){
    vis[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!vis[v])dfs2(v);
        else if(vis[v]==1){
            puts("NO");
            exit(0);
        }
    }
    vis[u]=2;
}
int top[N],tot;
int ans[N];
//2:Left 3:Right
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int opt,u,v;
        cin>>opt>>u>>v;
        G[opt].push_back({u,v});
        add(u,v);add(v,u);
    }
    for(int i=1;i<=n;i++)if(!col[i])dfs(i,2);
    memset(first,0,sizeof first);
    cnt=0;
    memset(deg,0,sizeof deg);

    for(auto i:G[1]){
        if(col[i.first]==2)add(i.first,i.second);
        else add(i.second,i.first);
    }
    for(auto i:G[2]){
        if(col[i.first]==2)add(i.second,i.first);
        else add(i.first,i.second);
    }
    for(int i=1;i<=n;i++)if(!vis[i])dfs2(i);

    queue<int> q;
    for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        top[now]=++tot;
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            deg[v]--;
            if(!deg[v])q.push(v);
        }
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        if(col[i]==2)cout<<"L ";
        else cout<<"R ";
        cout<<top[i]<<"\n";
    }
}