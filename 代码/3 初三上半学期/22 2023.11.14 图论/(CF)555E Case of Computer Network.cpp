#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int n,m,q;
struct node{
    int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],tot;
bool cut[N];
void Tarjan(int u,int fa) {
    dfn[u]=low[u]=++tot;
    for(int i=first[u];i;i=a[i].nex) {
        int v=a[i].v;
        if(!dfn[v]) {
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]) cut[i]=cut[i^1]=1;
        }
        else if(v!=fa) low[u]=min(low[u],dfn[v]);
    }
}
int col[N],sum;
void dfs(int u,int fa) {
    col[u]=sum;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        if(cut[i]||col[v]) continue;
        dfs(v,u);
    }
}
vector<int> G[N];
map<pair<int,int>,bool> mp;
struct node2{
    int u,v;
}b[N];
int fa[N][25],dep[N];
int belong[N],num;
void dfs2(int u,int dad) {
    belong[u]=num;
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<=20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int v:G[u]) {
        if(v==dad) continue;
        dfs2(v,u);
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int up[N],down[N];
bool check(int u,int dad) {
    for(int v:G[u]) {
        if(v==dad) continue;
        if(!check(v,u)||(up[v]&&down[v])) return false;
        up[u]+=up[v];
        down[u]+=down[v];
    }
    return true;
}
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,0);
    for(int i=1;i<=n;i++) if(!col[i]) sum++,dfs(i,0);
    for(int i=1;i<=n;i++) {
        for(int j=first[i];j;j=a[j].nex){
            int v=a[j].v;
            if(col[i]!=col[v]) {
                if(mp[{col[i],col[v]}]) continue;
                G[col[i]].push_back(col[v]);
                G[col[v]].push_back(col[i]);
                mp[{col[i],col[v]}]=1;
                mp[{col[v],col[i]}]=1;
            }
        }
    }
    for(int i=1;i<=sum;i++) if(!belong[i]) num++,dfs2(i,0);
    while(q--) {
        int u,v;
        cin>>u>>v;
        int newu=col[u],newv=col[v];
        if(newu==newv) continue;
        if(belong[newu]!=belong[newv]) {puts("No");return 0;}
        int lca=LCA(newu,newv);
        up[newu]++,up[lca]--;
        down[newv]++,down[lca]--;
    }
    for(int i=1;i<=sum;i++) {
        if(fa[i][0]==0) {
            if(!check(i,0)) {puts("No");return 0;}
        }
    }
    puts("Yes");
    return 0;
}
