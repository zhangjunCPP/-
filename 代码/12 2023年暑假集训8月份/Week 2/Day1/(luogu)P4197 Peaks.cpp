#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{
    int l,r,sum;
}tree[N<<4];
int tot;
void build(int &k,int l,int r){
    k=++tot;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(tree[k].l,l,mid);
    build(tree[k].r,mid+1,r);

}
void update(int pre,int &k,int l,int r,int x){
    k=++tot;
    tree[k]=tree[pre];
    tree[k].sum+=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(x<=mid) update(tree[pre].l,tree[k].l,l,mid,x);
    else  update(tree[pre].r,tree[k].r,mid+1,r,x);
}
int query(int l,int r,int x,int y,int k){
    if(l==r) {
        if(k==tree[x].sum-tree[y].sum)return l;
        else return 0;
    }
    int mid=(l+r)>>1;
    int d=tree[tree[x].r].sum-tree[tree[y].r].sum;
    if(k>d) return query(l,mid,tree[x].l,tree[y].l,k-d);
    else return query(mid+1,r,tree[x].r,tree[y].r,k);
}

struct node2{
    int u,v,w;
}e[N];
bool cmp(const node2 &x,const node2 &y){
    return x.w<y.w;
}

int n,m,q;
int h[N];
struct tmp{
    int id,val;
}hh[N];
bool cmp2(const tmp &x,const tmp &y){
    return x.val<y.val;
}
void init(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) {
        cin >> h[i];
        hh[i].val = h[i];
        hh[i].id = i;
    }
    sort(hh+1,hh+n+1,cmp2);
    for(int i=1;i<=n;i++) h[hh[i].id]=i;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        e[i]={u,v,w};
    }
}

struct node3{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}

int fa[N];
int find(int x){
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}

int val[N];
int sum;
void kruskal(){
    val[0]=0x3f3f3f3f;
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=n;i++) fa[i]=i;
    sum=n;
    for(int i=1;i<=m;i++){
        int u= find(e[i].u),v=find(e[i].v);
        if(u==v) continue;
        val[++sum]=e[i].w;
        fa[sum]=fa[u]=fa[v]=sum;
        add(sum,u),add(sum,v);
    }
}
int f[N][20];
int l[N],r[N];
int dfn;
int b[N];
void dfs(int u,int dad){
    f[u][0]=dad;
    for(int i=1;i<=19;i++)f[u][i]=f[f[u][i-1]][i-1];
    l[u]=dfn;
    if(first[u]==0) {
        b[++dfn]=u;
        r[u]=dfn;
        return;
    }
    for(int i=first[u];i;i=a[i].nex)dfs(a[i].v,u);
    r[u]=dfn;
}

int root[N];
int findd(int x,int k){
    for(int i=19;i>=0;i--){
        if(val[f[x][i]]<=k) x=f[x][i];
    }
    return x;
}
void solve(){
    dfs(sum,sum);
    build(root[0],1,n);
    for(int i=1;i<=dfn;i++)update(root[i-1],root[i],1,n,h[b[i]]);
    hh[0].val=-1;
    for(int i=1;i<=q;i++){
        int v,x,k;
        cin>>v>>x>>k;
        int now=findd(v,x);
        int ans=query(1,n,root[r[now]],root[l[now]],k);
        cout<<hh[ans].val<<"\n";
    }
}
signed main(){
    init();
    kruskal();
    solve();
}