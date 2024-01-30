#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m;
struct node{
    int v,w,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dep[N],fa[N],son[N],dis[N],siz[N];
int dfn[N],tot;
int val[N];
void dfs1(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u]=dad;
    siz[u]=1;
    dfn[++tot]=u;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dis[v]=dis[u]+a[i].w;
        val[v]=a[i].w;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
int top[N];
void dfs2(int u){
    if(son[u]) {
        int v=son[u];
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex) {
        int v=a[i].v;
        if(!top[v]) {
            top[v]=v;
            dfs2(v);
        }
    }
}
int lca(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy) {
        if(dep[fx]<=dep[fy]) {
            swap(fx,fy);
            swap(x,y);
        }
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>=dep[y]) swap(x,y);
    return x;
}
int getdis(int x,int y){return dis[x]+dis[y]-2*dis[lca(x,y)];}
struct node2{int x,y,ans;}q[N];

int MAX=-1;
int c[N];
bool check(int mid){
    memset(c,0,sizeof c);
    int sum=0;
    for(int i=1;i<=m;i++){
        if(q[i].ans>mid){
            c[q[i].x]++;
            c[q[i].y]++;
            c[lca(q[i].x,q[i].y)]-=2;
            sum++;
        }
    }
    for(int i=n;i>=1;i--) {
        int now=dfn[i];
        c[fa[now]]+=c[now];
        if(c[now]==sum&&val[now]>=MAX-mid) return true;
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<n;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs1(1,0);
    top[1]=1;
    dfs2(1);
    for(int i=1;i<=m;i++) {
        cin>>q[i].x>>q[i].y;
        q[i].ans=getdis(q[i].x,q[i].y);
        MAX=max(MAX,q[i].ans);
    }
    int l=0,r=1e9+10,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
}