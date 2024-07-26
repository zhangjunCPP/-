#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,K=5e5;//K用来区分第一棵树和第二棵树
struct node{
    int v,nex,w;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,first[u],w};
    first[u]=cnt;
}
int tree[N];
void build(int k,int l,int r){
    if(l==r){
        tree[l]=k;
        return;
    }
    int mid=(l+r)>>1;
    add(k,k<<1,0),add(k,k<<1|1,0);
    add((k<<1)+K,k+K,0),add((k<<1|1)+K,k+K,0);
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
void modify(int k,int l,int r,int x,int y,int id,int w,int opt){
    if(l>=x&&r<=y){
        if(opt==2)add(id+K,k,w);
        else add(k+K,id,w);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)modify(k<<1,l,mid,x,y,id,w,opt);
    if(y>mid)modify(k<<1|1,mid+1,r,x,y,id,w,opt);
}
struct node2{
    int id,val;
    bool operator<(const node2& b) const{
        return val>b.val;
    }
};
int dis[N];
bool vis[N];
void dij(int s){
    priority_queue<node2> q;
    memset(dis,0x3f,sizeof dis);
    memset(vis, false,sizeof vis);
    dis[s]=0;
    q.push({s,0});
    while (!q.empty()){
        node2 now=q.top();
        q.pop();
        int u=now.id;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]>dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                q.push({v,dis[v]});
            }
        }
    }
}
int r,c,n;
bool mp[N];
int f(int x,int y) {
    return (x-1)*c+y;
}
int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
signed main(){
    freopen("stamp.in","r",stdin);
    freopen("stamp.out","w",stdout);
    // int n,q,s;
    // cin>>n>>q>>s;
    // build(1,1,n);
    // for(int i=1;i<=n;i++){
    //     add(tree[i],tree[i]+K,0);
    //     add(tree[i]+K,tree[i],0);
    // }
    // for(int i=1;i<=q;i++){
    //     int opt;
    //     cin>>opt;
    //     if(opt==1){
    //         int u,v,w;
    //         cin>>u>>v>>w;
    //         add(tree[u]+K,tree[v],w);
    //     }
    //     else {
    //         int v,l,r,w;
    //         cin>>v>>l>>r>>w;
    //         modify(1, 1, n,l,r,tree[v],w,opt);
    //     }
    // }
    // dij(tree[s]+K);
    // for(int i=1;i<=n;i++){
    //     if(dis[tree[i]]==0x3f3f3f3f3f3f3f3fll) cout<<-1<<" ";
    //     else cout<<dis[tree[i]]<<" ";
    // }
    cin>>r>>c>>n;
    build(1,1,r*c);
    int x_1,y_1,x_2,y_2;
    cin>>x_1>>y_1>>x_2>>y_2;
    int st=f(x_1,y_1),ed=f(x_2,y_2);
    for(int i=1;i<=r;i++) {
        string s;
        cin>>s;
        for(int j=1;j<=c;j++)mp[f(i,j)]=(s[j-1]=='.');
    }
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            int u=f(i,j);
            for(int k=0;k<4;k++){
                int x=i+dx[k];
                int y=j+dy[k];
                if(x>r||x<1||y>c||y<1)continue;
                int v=f(x,y);
                if(mp[v]) {
                    printf("u=(%lld,%lld) v=(%lld,%lld)\n",i,j,x,y);
                    add(tree[u]+K,tree[v],0);
                }
            }
        }
    }
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            int u=f(i,j);
            for(int k=1;k<=n;k++) {
                int L=f(min(r,i+k-1),j);
                int R=f(min(r,i+k-1),min(c,j+n-1));
                printf("u=(%lld,%lld) -> L=(%lld,%lld),R=(%lld,%lld)\n",i,j,min(r,i+k-1),j,min(r,i+k-1),min(c,j+n-1));
                modify(1, 1, r*c,L,R,tree[u],1,2);
            }
        }
    }
    dij(tree[st]+K);
    cout<<dis[tree[ed]];
}