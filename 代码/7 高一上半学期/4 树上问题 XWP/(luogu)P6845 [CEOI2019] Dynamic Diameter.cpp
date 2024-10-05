#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e18;
struct node{
    int v,w;
    int id;
};
vector<node> G[N];
void add(int u,int v,int w,int id){
    G[u].push_back({v,w,id});
}
int dfn,val[N];
int L[N],R[N];
int dep[N];
int w[N];
int rev[N];
void dfs(int u,int fa,int id){
    rev[id]=u;
    dfn++;
    L[u]=R[u]=dfn;
    val[dfn]=dep[u];
    for(auto it:G[u]){
        int v=it.v;
        if(v==fa)continue;
        dep[v]=dep[u]+it.w;
        w[v]=it.w;
        dfs(v,u,it.id);
        dfn++;
        R[u]=dfn;
        val[dfn]=dep[u];
    }
}
#define ls (k<<1)
#define rs (k<<1|1)
struct node2{
    int Max,Min;
    int lMax,rMax;
    int ans;
    int lazy;
    node2 operator+(const node2&oth)const{
        node2 tmp={
            max(Max,oth.Max),min(Min,oth.Min),
            max({lMax,oth.lMax,Max-2*oth.Min}),max({rMax,oth.rMax,oth.Max-2*Min}),
            max({ans,oth.ans,lMax+oth.Max,Max+oth.rMax}),
            0
        };
        return tmp;
    }
}tree[N*4];
void modify(int k,int val){
    tree[k].lazy+=val;
    tree[k].Max+=val,tree[k].Min+=val;
    tree[k].lMax-=val,tree[k].rMax-=val;
}
void pushdown(int k){
    if(tree[k].lazy){
        modify(ls,tree[k].lazy);
        modify(rs,tree[k].lazy);
        tree[k].lazy=0;
    }
}
void build(int k,int l,int r){
    if(l==r){
        tree[k]={val[l],val[l],-INF,-INF,-INF,0};
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    tree[k]=tree[ls]+tree[rs];
}
void update(int k,int l,int r,int x,int y,int val){
    if(x<=l&&y>=r){
        modify(k,val);
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(x<=mid)update(ls,l,mid,x,y,val);
    if(y>mid)update(rs,mid+1,r,x,y,val);
    tree[k]=tree[ls]+tree[rs];
}

signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    
    int n,q,mod;
    cin>>n>>q>>mod;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w,i);
        add(v,u,w,i);
    }
    dfs(1,0,0);
    build(1,1,dfn);
    int last=0;
    while(q--){
        int d,e;
        cin>>d>>e;
        d=rev[(d+last)%(n-1)+1];
        e=(e+last)%mod;
        update(1,1,dfn,L[d],R[d],e-w[d]);
        w[d]=e;
        last=max(tree[1].Max,tree[1].ans);
        cout<<last<<"\n";
    }
    return 0;
}