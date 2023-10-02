#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=998244353;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int s[N];
int n,m,id;
int fa[N][20];
int dep[N];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs(v,u);
    }
}
int LCA(int x,int y){
    if(dep[x]<=dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) {
        if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--) {
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans%mod;
}
int fac[N],inv[N];
void init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}
int calc(int x){return (C(2*x,x)-C(2*x,x+1)%mod+mod)%mod;}   //¿¨ÌØÀ¼Êý
int g[N][20];
int val[N];
void dfs2(int u,int top){
    g[u][0]=fa[top][0];
    for(int i=1;i<20;i++) g[u][i]=g[g[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa[u][0]) continue;
        if(s[u]==s[v]){
            val[v]=val[top]*calc(dep[v]-dep[top]+1)%mod;
            dfs2(v,top);
        }
        else {
            val[v]=val[u]%mod;
            dfs2(v,v);
        }
    }
}
void work(int x,int y){
    int lca=LCA(x,y);
    int fx=x,fy=y;
    for(int i=19;i>=0;i--) if(dep[g[fx][i]]>=dep[lca]) fx=g[fx][i];
    for(int i=19;i>=0;i--) if(dep[g[fy][i]]>=dep[lca]) fy=g[fy][i];
    int d=dep[x]+dep[y]-2*dep[lca]+1;
    int ans=val[x]*val[y]%mod;
    ans=ans*qpow(val[fx]*val[fy]%mod,mod-2)%mod;
    ans=ans*calc(dep[fx]+dep[fy]-2*dep[lca]+1)%mod;
    ans=ans*C(m,2*d)%mod;
    cout<<ans%mod<<"\n";
}
signed main(){
    init();
    cin>>n>>m>>id;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    val[0]=val[1]=1;
    dfs2(1,1);
    int Q;
    cin>>Q;
    while(Q--){
        int x,y;
        cin>>x>>y;
        work(x,y);
    }
}