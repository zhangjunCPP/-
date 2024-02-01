#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int rt;
int siz[N];
int n;
void dfs1(int u,int dad){
    siz[u]=1;
    int Max=0;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        Max=max(Max,siz[v]);
    }
    Max=max(Max,n-siz[u]);
    if(Max*2<=n) rt=u;
}
int son1[N],son2[N];
void dfs2(int u,int dad){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs2(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son1[u]]) son2[u]=son1[u],son1[u]=v;
        else if(siz[v]>siz[son2[u]]) son2[u]=v;
    }
}
bool ans[N];
void dfs3(int u,int dad,int Max){
    if((n-siz[u]-Max)*2<=n||u==rt)ans[u]=true;

    if((n-siz[u])*2<=n) Max=max(Max,n-siz[u]);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        if(son1[u]==v) dfs3(v,u,max(Max,siz[son2[u]]));
        else dfs3(v,u,max(Max,siz[son1[u]]));
    }
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(rt,0);
    dfs3(rt,0,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}