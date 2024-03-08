#include <bits/stdc++.h>

#define int long long
using namespace std;
const int N=5e6+10,INF=1e18;
int n,m;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int siz[N],son[N],dep[N],fa[N];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u]=dad;
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
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
        dfs2(v);
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
    int lmx[2]={0,0},rmx[2]={0,0};
    int dis[2][2]={0,0,0,0};
    node2 operator+(const node2&oth)const{
        node2 ans;
        ans.lmx[0]=max({lmx[0],dis[0][0]+oth.lmx[0],dis[0][1]+oth.lmx[1]});
        ans.lmx[1]=max({lmx[1],dis[1][0]+oth.lmx[0],dis[1][1]+oth.lmx[1]});
        ans.rmx[0]=max({oth.rmx[0],oth.dis[0][0]+rmx[0],oth.dis[1][0]+rmx[1]});
        ans.rmx[1]=max({oth.rmx[1],oth.dis[0][1]+rmx[0],oth.dis[1][1]+rmx[1]});
        for(int i=0;i<=1;i++)
            for(int j=0;j<=1;j++){
                ans.dis[i][j]=-INF;
                for(int k=0;k<=1;k++)ans.dis[i][j]=max({ans.dis[i][j],dis[i][k]+oth.dis[k][j]});
            }
        return ans;
    }
}tree[N];

void modify(int k,int x,int y){
    tree[k].lmx[0]=tree[k].rmx[0]=x;
    tree[k].lmx[1]=tree[k].rmx[1]=y;
    tree[k].dis[0][0]=x?x:-INF;
    tree[k].dis[1][1]=y?y:-INF;
    tree[k].dis[0][1]=tree[k].dis[1][0]=x&&y?x+y:-INF;
}
void update(int k,int l,int r,int x,int val1,int val2){
    if(l==r){
        modify(k,val1,val2);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update(k<<1,l,mid,x,val1,val2);
    else update(k<<1|1,mid+1,r,x,val1,val2);
    tree[k]=tree[k<<1]+tree[k<<1|1];
}
node2 query(int k,int l,int r,int x,int y){
    if(x<=l&&y>=r)return tree[k];
    int mid=(l+r)>>1;
    if(x>mid)return query(k<<1|1,mid+1,r,x,y);
    if(y<=mid)return query(k<<1,l,mid,x,y);
    return query(k<<1,l,mid,x,mid)+query(k<<1|1,mid+1,r,mid+1,y);
}

int ask(int x,int y){
    node2 ansx,ansy;
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]>dep[fy]){
            ansx=query(1,1,n,id[fx],id[x])+ansx;
            x=fa[fx];
            fx=top[x];
        }
        else{
            ansy= query(1,1,n,id[fy],id[y])+ansy;
            y=fa[fy];
            fy=top[y];
        }
    }
    if(dep[x]>dep[y]) ansx=query(1,1,n,id[y],id[x])+ansx;
    else ansy= query(1,1,n,id[x],id[y])+ansy;
    swap(ansx.lmx[0],ansx.rmx[0]);
    swap(ansx.lmx[1],ansx.rmx[1]);
    swap(ansx.dis[0][1],ansx.dis[1][0]);
    ansx=ansx+ansy;
    return max(ansx.lmx[0],ansx.lmx[1]);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    top[1]=1;
    id[1]=++tot;
    dfs2(1);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        update(1,1,n,id[i],s[0]=='.',s[1]=='.');
    }
    while(m--){
        string opt;
        cin>>opt;
        if(opt=="C"){
            int u;
            string s;
            cin>>u>>s;
            update(1,1,n,id[u],s[0]=='.',s[1]=='.');
        }
        else{
            int u,v;
            cin>>u>>v;
            cout<<ask(u,v)<<"\n";
        }
    }
}