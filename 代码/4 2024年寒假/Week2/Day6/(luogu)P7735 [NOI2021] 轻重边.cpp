#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=1e6+10;

struct node{
    int v,nex;
} a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

int dep[N],siz[N],son[N],fa[N];
void dfs1(int u,int dad){
    siz[u]=1;
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}

int id[N],tot;
int top[N];
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        id[v]=++tot;
        dfs2(son[u]);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(top[v])continue;
        top[v]=v;
        id[v]=++tot;
        dfs2(v);
    }
}

struct node2{
    int sum=0;
    int lc,rc=0;
    int lazy=0;
    node2 operator+(const node2 &oth){
        if(!lc)return oth;
        if(!oth.lc)return *this;
        node2 ans;
        ans.sum=sum+oth.sum+(rc==oth.lc);
        ans.lc=lc;
        ans.rc=oth.rc;
        ans.lazy=0;
        return ans;
    }
}tree[N*4];
void update(int k,int l,int r,int c){
    tree[k].sum=r-l;
    tree[k].lc=tree[k].rc=c;
    tree[k].lazy=c;
}
void pushdown(int k,int l,int r){
    if(tree[k].lazy){
        int mid=(l+r)>>1;
        update(ls,l,mid,tree[k].lazy);
        update(rs,mid+1,r,tree[k].lazy);
        tree[k].lazy=0;
    }
}
void build(int k,int l,int r){
    if(l==r){
        tree[k]={0,l,l,0};
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    tree[k]=tree[ls]+tree[rs];
}
void change(int k,int l,int r,int x,int y,int val){
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        update(k,l,r,val);
        return;
    }
    int mid=(l+r)>>1;
    pushdown(k,l,r);
    change(ls,l,mid,x,y,val);
    change(rs,mid+1,r,x,y,val);
    tree[k]=tree[ls]+tree[rs];
}
node2 query(int k,int l,int r,int x,int y){
    if(x<=l&&r<=y)return tree[k];
    int mid=(l+r)>>1;
    pushdown(k,l,r);
    if(y<=mid)return query(ls,l,mid,x,y);
    if(x>mid)return query(rs,mid+1,r,x,y);
    return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
}
void init(){
    memset(first,0,sizeof first);
    memset(son,0,sizeof son);
    memset(top,0,sizeof top);
    cnt=0;
    tot=0;
}
int now;
int n,m;
void modify(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy]){swap(fx,fy);swap(x,y);}
        change(1,1,n,id[fx],id[x],now);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    change(1,1,n,id[x],id[y],now);
}
int ask(int x,int y){
    node2 ans1,ans2;
    ans1.sum=ans2.sum=0;
    ans1.lc=ans2.lc=ans1.rc=ans2.rc=0;
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]>dep[fy]){
            ans1=query(1,1,n,id[fx],id[x])+ans1;
            x=fa[fx];
            fx=top[x];
        }
        else{
            ans2=query(1,1,n,id[fy],id[y])+ans2;
            y=fa[fy];
            fy=top[y];
        }
    }
    if(dep[x]>dep[y])ans1=query(1,1,n,id[y],id[x])+ans1;
    else ans2=query(1,1,n,id[x],id[y])+ans2;
    swap(ans1.lc,ans1.rc);
    return (ans1+ans2).sum;
}
void solve(){
    init();
    cin>>n>>m;
    now=n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    top[1]=1;
    id[1]=++tot;
    dfs2(1);
    build(1,1,n);
    while(m--){
        int opt,u,v;
        cin>>opt>>u>>v;
        if(opt==1) {
            now++;
            modify(u,v);
        }
        if(opt==2)cout<<ask(u,v)<<"\n";
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}