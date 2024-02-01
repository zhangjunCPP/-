#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=6e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int n;
ll ans;
int fa[N];
int siz[N];
int son1[N],son2[N];
void init() {
    memset(first,0,sizeof first);
    cnt=0;
    memset(fa,0,sizeof fa);
    memset(son1,0,sizeof son1);
    ans=0;
}

int f[N][17];
void dfs(int u,int dad){
    siz[u]=1;
    fa[u]=dad;
    for(int i=first[u];i;i=a[i].nex) {
        int v=a[i].v;
        if(v==dad) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son1[u]]) son2[u]=son1[u],son1[u]=v;
        else if(siz[v]>siz[son2[u]]) son2[u]=v;
    }
    f[u][0]=son1[u];
    for(int i=1;i<17;i++) f[u][i]=f[f[u][i-1]][i-1];
}

int siz2[N],fa2[N];
int son3[N];
void dfs2(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        siz2[u]=siz[1]-siz[v];
        fa2[u]=0,fa2[v]=0;
        if(v==son1[u]) son3[u]=son2[u];
        else son3[u]=son1[u];
        if(siz2[dad]>siz2[son3[u]]) son3[u]=dad;
        f[u][0]=son3[u];
        for(int j=1;j<17;j++) f[u][j]=f[f[u][j-1]][j-1];
        int b=u;
        for(int j=16;j>=0;j--)if(siz2[u]-siz2[f[b][j]]<=siz2[u]/2) b=f[b][j];
        ans+=b;
        if(max(siz2[son3[fa2[b]]],siz2[u]-siz2[fa2[b]])<=siz2[u]/2) ans+=fa2[b];
        b=v;
        for(int j=16;j>=0;j--)if(siz2[v]-siz2[f[b][j]]<=siz2[v]/2) b=f[b][j];
        ans+=b;
        if(max(siz2[son3[fa2[b]]],siz2[v]-siz2[fa2[b]])<=siz2[v]/2) ans+=fa2[b];
        fa2[u]=v;
        dfs2(v,u);
    }
    son3[u]=son1[u];
    siz2[u]=siz[u];
    fa2[u]=fa[u];
    f[u][0]=son1[u];
    for(int i=1;i<17;i++) f[u][i]=f[f[u][i-1]][i-1];
}
void solve(){
    init();
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) fa2[i]=fa[i],siz2[i]=siz[i],son3[i]=son1[i];
    dfs2(1,0);
    cout<<ans<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
}