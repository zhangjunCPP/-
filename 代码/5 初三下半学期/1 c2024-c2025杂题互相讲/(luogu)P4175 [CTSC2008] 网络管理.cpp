#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,MAX=1e8;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int siz[N],fa[N],dep[N],son[N];
int dfn[N],tot;
void dfs1(int u,int dad){
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    siz[u]=1;
    dfn[u]=++tot;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs1(v,u);
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
int lca(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
int n,q;
int lowbit(int x){return x&(-x);}
struct node2{
    int ls,rs,val;
}tree[N*100];
int tot2;
void update(int &k,int l,int r,int x,int val){
    if(!k)k=++tot2;
    tree[k].val+=val;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)update(tree[k].ls,l,mid,x,val);
    else update(tree[k].rs,mid+1,r,x,val);
}
int rt[N];
void add(int x,int y,int val){for(int i=x;i<=n;i+=lowbit(i))update(rt[i],1,MAX,y,val);}
int num[2];
int need[2][N];
void ask(int x,int opt){for(int i=x;i;i-=lowbit(i))need[opt][++num[opt]]=rt[i];}
int query(int l,int r,int k){
    if(l==r)return l;
    int sum=0;
    int all=0;
    for(int i=1;i<=num[1];i++)sum+=tree[tree[need[1][i]].rs].val,all+=tree[need[1][i]].val;
    for(int i=1;i<=num[0];i++)sum-=tree[tree[need[0][i]].rs].val,all-=tree[need[0][i]].val;
    if(all<k)return -1;
    int mid=(l+r)>>1;
    if(k>sum){
        for(int i=1;i<=num[1];i++)need[1][i]=tree[need[1][i]].ls;
        for(int i=1;i<=num[0];i++)need[0][i]=tree[need[0][i]].ls;
        return query(l,mid,k-sum);
    }
    else {
        for(int i=1;i<=num[1];i++)need[1][i]=tree[need[1][i]].rs;
        for(int i=1;i<=num[0];i++)need[0][i]=tree[need[0][i]].rs;
        return query(mid+1,r,k);
    }
}
int t[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>t[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    top[1]=1;
    dfs2(1);
    for(int i=1;i<=n;i++){
        add(dfn[i],t[i],1);
        add(dfn[i]+siz[i]-1+1,t[i],-1);
    }
    while(q--){
        int k,x,y;
        cin>>k>>x>>y;
        if(k==0){
            add(dfn[x],t[x],-1);
            add(dfn[x]+siz[x]-1+1,t[x],1);
            t[x]=y;
            add(dfn[x],t[x],1);
            add(dfn[x]+siz[x]-1+1,t[x],-1);
        }
        else{
            num[0]=num[1]=0;
            int LCA=lca(x,y);
            ask(dfn[x],1),ask(dfn[y],1);
            ask(dfn[LCA],0),ask(dfn[fa[LCA]],0);
            int ans= query(1,MAX,k);
            if(ans==-1)cout<<"invalid request!\n";
            else cout<<ans<<"\n";
        }
    }
}