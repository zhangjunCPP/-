#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N],fa[N][20];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
struct node2{
    int ls,rs;
    int id,sum;
}tree[N*50];
int tot;
void pushup(int k){
    int ls=tree[k].ls,rs=tree[k].rs;
    if(tree[ls].sum>=tree[rs].sum)tree[k].sum=tree[ls].sum,tree[k].id=tree[ls].id;
    else tree[k].sum=tree[rs].sum,tree[k].id=tree[rs].id;
}
void change(int &k,int l,int r,int x,int val){
    if(!k)k=++tot;
    if(l==r){
        tree[k].id=l,tree[k].sum+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)change(tree[k].ls,l,mid,x,val);
    else change(tree[k].rs,mid+1,r,x,val);
    pushup(k);
}
void merge(int &x,int y,int l,int r){
    if(!x||!y){x|=y;return;}
    if(l==r){tree[x].sum+=tree[y].sum;return;}
    int mid=(l+r)>>1;
    merge(tree[x].ls,tree[y].ls,l,mid);
    merge(tree[x].rs,tree[y].rs,mid+1,r);
    pushup(x);
}
int rt[N];
int ans[N];
void calc(int u,int dad){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        calc(v,u);
        merge(rt[u],rt[v],1,N-5);
    }
    if(tree[rt[u]].sum)ans[u]=tree[rt[u]].id;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int u,v,z;
        cin>>u>>v>>z;
        change(rt[u],1,N-5,z,1);
        change(rt[v],1,N-5,z,1);
        int lca=LCA(u,v);
        change(rt[lca],1,N-5,z,-1);
        change(rt[fa[lca][0]],1,N-5,z,-1);
    }
    calc(1,0);
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}