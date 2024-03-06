#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e18;
const int N=1e6+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int vis[N];
int ring[N],tot;
int val[N];
int dfs1(int u,int fa){
    if(vis[u])return u;
    vis[u]=-1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        int tmp=dfs1(v,u);
        if(tmp){
            ring[++tot]=u;
            vis[u]=1;
            val[tot]=a[i].w;
            return tmp==u?0:tmp;
        }
    }
    return 0;
}
int ans1,ans2;
int f[N];
void dfs2(int u,int fa){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        if(vis[v]==1)continue;
        dfs2(v,u);
        ans1=max(ans1,f[u]+a[i].w+f[v]);
        f[u]=max(f[u],f[v]+a[i].w);
    }
}
int l1[N],l2[N];
int r1[N],r2[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs1(1,0);
    for(int i=1;i<=tot;i++)dfs2(ring[i],0);

    for(int i=1;i<=tot;i++)val[i]+=val[i-1];
    int res=-INF;
    l1[0]=l2[0]=-INF;
    for(int i=1;i<=tot;i++){
        l1[i]=max(l1[i-1],f[ring[i]]+val[i]);
        l2[i]=max(l2[i-1],f[ring[i]]+val[i]+res);
        res=max(res,f[ring[i]]-val[i]);
    }
    res=r1[tot+1]=r2[tot+1]=-INF;
    for(int i=tot;i>=1;i--){
        r1[i]=max(r1[i+1],f[ring[i]]+val[tot]-val[i]);
        r2[i]=max(r2[i+1],f[ring[i]]-val[i]+res);
        res=max(res,f[ring[i]]+val[i]);
    }
    ans2=INF;
    for(int i=1;i<=tot;i++)ans2=min(ans2,max({l1[i-1]+r1[i],l2[i-1],r2[i]}));
    cout<<max(ans1,ans2);
}