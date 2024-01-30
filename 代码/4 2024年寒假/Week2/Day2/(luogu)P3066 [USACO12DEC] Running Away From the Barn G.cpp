#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dep[N];
int fa[N][25];
int len[N];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<25;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        len[v]=len[u]+a[i].w;
        dfs(v,u);
    }
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=24;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=24;i>=0;i--){
        if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    }
    return fa[x][0];
}


int calc(int u,int t){
    int ans=u;
    for(int i=24;i>=0;i--){
        if(len[u]-len[fa[ans][i]]<=t) ans=fa[ans][i];
    }
    return ans;
}
int diff[N];
void solve(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        solve(v,u);
        diff[u]+=diff[v];
    }
}
signed main(){
    int n,t;
    cin>>n>>t;
    for(int i=2;i<=n;i++){
        int x,w;
        cin>>x>>w;
        add(x,i,w);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        int ans=calc(i,t);
        //lca(i,ans)=ans
        diff[i]++;
        diff[fa[ans][0]]--;
    }
    solve(1,0);
    for(int i=1;i<=n;i++)cout<<diff[i]<<"\n";
    return 0;
}