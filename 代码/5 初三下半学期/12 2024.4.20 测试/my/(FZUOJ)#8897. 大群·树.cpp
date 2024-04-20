#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N],siz[N],son[N],fa[N];
void dfs(int u,int dad){
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int top[N];
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(top[v])continue;
        top[v]=v;
        dfs2(v);
    }
}
int LCA(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
int dis(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    top[1]=1;
    dfs2(1);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(dis(i,j)>k)continue;
            for(int l=j+1;l<=n;l++){
                if(dis(j,l)>k||dis(i,l)>k)continue;
                ans++;
            }
        }
    }
    cout<<ans;
}