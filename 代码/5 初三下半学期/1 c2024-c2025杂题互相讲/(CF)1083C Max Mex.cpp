#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dep[N];
int dfn[N],tot;
int st[N][20];
void dfs(int u){
    dfn[u]=++tot;
    st[tot][0]=u;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        dep[v]=dep[u]+1;
        dfs(v);
        st[++tot][0]=u;
    }
}
int chk(int x,int y){return dep[x]<dep[y]?x:y;}
int lg[N];
void get_lca(){
    dfs(1);
    lg[1]=0;
    for(int i=2;i<N;i++)lg[i]=lg[i>>1]+1;
    for(int j=1;j<19;j++)for(int i=1;i+(1<<j)-1<=tot;i++)st[i][j]=chk(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int lca(int x,int y){
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    int tmp=lg[y-x+1];
    return chk(st[x][tmp],st[y-(1<<tmp)+1][tmp]);
}
int dis(int x,int y){
    int LCA=lca(x,y);
    return dep[x]+dep[y]-2*dep[LCA];
}
int mp[N];
struct node2{
    int l,r;
}tree[N];
bool check(int u,int v,int x,int y){
    return dis(u,x)+dis(u,y)==dis(x,y)&&dis(v,x)+dis(v,y)==dis(x,y);
}
node2 merge(node2 x,node2 y){
    if(!x.l||!y.l)return{0,0};
    if(check(y.l,y.r,x.l,x.r))return {x.l,x.r};
    if(check(x.l,x.r,y.l,y.r))return {y.l,y.r};
    if(check(x.r,y.r,x.l,y.l))return {x.l,y.l};
    if(check(x.r,y.l,x.l,y.r))return {x.l,y.r};
    if(check(x.l,y.r,x.r,y.l))return {x.r,y.l};
    if(check(x.l,y.l,x.r,y.r))return {x.r,y.r};
    return {0,0};
}
void pushup(int k){tree[k]=merge(tree[k<<1],tree[k<<1|1]);}
void build(int k,int l,int r){
    if(l==r){
        tree[k]={mp[l],mp[l]};
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}
void modify(int k,int l,int r,int x,int y){
    if(l==r){
        tree[k]={y,y};
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)modify(k<<1,l,mid,x,y);
    else modify(k<<1|1,mid+1,r,x,y);
    pushup(k);
}
int query(int k,int l,int r,node2 ans){
    if(l==r)return r;
    int mid=(l+r)>>1;
    node2 tmp=(ans.l==0&&ans.r==0)?tree[k<<1]:merge(ans,tree[k<<1]);
    if(tmp.l)return query(k<<1|1,mid+1,r,tmp);
    else return query(k<<1,l,mid,ans);
}
int n;
int p[N];
int deg[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){cin>>p[i];p[i]++;mp[p[i]]=i;}
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        add(x,i);
        deg[x]++;
    }
    bool flag=true;
    for(int i=1;i<=n;i++)if(deg[i]>1)flag=false;
    get_lca();
    build(1,1,n);
    int q;
    cin>>q;
    while(q--){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,y;
            cin>>x>>y;
            modify(1,1,n,p[x],y);
            modify(1,1,n,p[y],x);
            swap(p[x],p[y]);
        }
        else{
            if(flag)cout<<n<<"\n";
            else cout<<query(1,1,n,{0,0})-1<<"\n";
        }
    }
}