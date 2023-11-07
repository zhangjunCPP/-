#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n;
int val[N];
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int siz[N],fa[N],son[N],dep[N];
void dfs1(int u,int dad) {
    fa[u]=dad;
    dep[u]=dep[dad]+1;
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex) {
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}

int top[N];
int id[N],seq[N],tot;
void dfs2(int u) {
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        id[v]=++tot;
        seq[id[v]]=v;
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex) {
        int v=a[i].v;
        if(!top[v]) {
            top[v]=v;
            id[v]=++tot;
            seq[id[v]]=v;
            dfs2(v);
        }
    }
}
int tree1[N<<2],tree2[N<<2];
void build(int k,int l,int r){
    if(l==r) {
        tree1[k]=tree2[k]=val[seq[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree1[k]=max(tree1[k<<1],tree1[k<<1|1]);
    tree2[k]=tree2[k<<1]+tree2[k<<1|1];
}
void update(int k,int l,int r,int x,int y) {
    if(l==r) {
        tree1[k]=tree2[k]=y;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(k<<1,l,mid,x,y);
    else update(k<<1|1,mid+1,r,x,y);
    tree1[k]=max(tree1[k<<1],tree1[k<<1|1]);
    tree2[k]=tree2[k<<1]+tree2[k<<1|1];
}
int ans1,ans2;
void query(int k,int l,int r,int x,int y){
    if(x>r||y<l) return;
    if(x<=l&&y>=r) {
        ans1=max(ans1,tree1[k]);
        ans2=ans2+tree2[k];
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) query(k<<1,l,mid,x,y);
    if(y>mid) query(k<<1|1,mid+1,r,x,y);
}
void ask(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy]) {
            swap(x,y);
            swap(fx,fy);
        }
        query(1,1,n,id[fx],id[x]);
        x=fa[fx];
        fx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    query(1,1,n,id[x],id[y]);
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++) cin>>val[i];
    dfs1(1,1);
    top[1]=1;
    id[1]=++tot;
    seq[id[1]]=1;
    dfs2(1);
    build(1,1,n);
    int q;
    cin>>q;
    while(q--) {
        ans1=-1000000,ans2=0;
        string s;
        int x,y;
        cin>>s>>x>>y;
        if(s=="CHANGE") { update(1, 1, n, id[x], y);}
        else ask(x,y);
        if(s=="QMAX") cout<<ans1<<"\n";
        if(s=="QSUM") cout<<ans2<<"\n";
    }
}