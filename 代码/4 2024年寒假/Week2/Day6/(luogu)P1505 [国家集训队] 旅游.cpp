#include <bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=5e6+10;
const int INF=0x3f3f3f3f;
int n;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int val[N];
int fa[N],siz[N],son[N],dep[N];
void dfs1(int u,int dad){
    fa[u]=dad;
    siz[u]=1;
    dep[u]=dep[dad]+1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        val[v]=a[i].w;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int top[N];
int id[N],tot,rev[N];
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        id[v]=++tot;
        rev[id[v]]=v;
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(top[v])continue;
        top[v]=v;
        id[v]=++tot;
        rev[id[v]]=v;
        dfs2(v);
    }
}

int tree1[N],tree2[N],tree3[N];
void pushup(int k){
    tree1[k]=tree1[ls]+tree1[rs];
    tree2[k]=max(tree2[ls],tree2[rs]);
    tree3[k]=min(tree3[ls],tree3[rs]);
}
void build(int k,int l,int r){
    if(l==r){
        tree1[k]=tree2[k]=tree3[k]=val[rev[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
int lazy[N];
void update(int k){
    lazy[k]^=1;
    int tmp1=tree2[k],tmp2=tree3[k];
    tree1[k]=-tree1[k];
    tree2[k]=-tmp2;
    tree3[k]=-tmp1;
}
void pushdown(int k){
    if(lazy[k]){
        update(ls);
        update(rs);
        lazy[k]=0;
    }
}
void change1(int k,int l,int r,int x,int y){ //单点修改
    if(l==r){
        tree1[k]=tree2[k]=tree3[k]=y;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid)change1(ls,l,mid,x,y);
    else change1(rs,mid+1,r,x,y);
    pushup(k);
}
void change2(int k,int l,int r,int x,int y){//区间修改
    if(l>y||r<x)return;
    if(x<=l&&y>=r){
        update(k);
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid)change2(ls,l,mid,x,y);
    if(y>mid)change2(rs,mid+1,r,x,y);
    pushup(k);
}
int ans1,ans2,ans3;
void query(int k,int l,int r,int x,int y){//区间查询
    if(l>y||r<x)return;
    if(x<=l&&y>=r){
        ans1+=tree1[k];
        ans2=max(ans2,tree2[k]);
        ans3=min(ans3,tree3[k]);
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid)query(ls,l,mid,x,y);
    if(y>mid)query(rs,mid+1,r,x,y);
}
void ask(int x,int y){//树上查询
    ans1=0,ans2=-INF,ans3=INF;
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy]){swap(fx,fy);swap(x,y);}
        query(1,1,n,id[fx],id[x]);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    if(x!=y)query(1,1,n,id[x]+1,id[y]);
}
void modify(int x,int y){//树上修改
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy]){swap(fx,fy);swap(x,y);}
        change2(1,1,n,id[fx],id[x]);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    if(x!=y)change2(1,1,n,id[x]+1,id[y]);
}
int x[N],y[N];
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u++,v++;
        add(u,v,w);
        add(v,u,w);
        x[i]=u,y[i]=v;
    }
    dfs1(1,0);
    top[1]=1;
    id[1]=++tot;
    rev[id[1]]=1;
    dfs2(1);
    build(1,1,n);
    int m;
    cin>>m;
    while(m--){
        string opt;
        int u,v;
        cin>>opt>>u>>v;
        if(opt=="C"){
            int tmp1=x[u],tmp2=y[u];
            if(dep[tmp1]<dep[tmp2])swap(tmp1,tmp2);
            change1(1,1,n,id[tmp1],v);
            continue;
        }
        u++,v++;
        if(opt=="N"){modify(u,v);continue;}
        ask(u,v);
        if(opt=="SUM")cout<<ans1<<"\n";
        else if(opt=="MAX")cout<<ans2<<"\n";
        else cout<<ans3<<"\n";
    }
}