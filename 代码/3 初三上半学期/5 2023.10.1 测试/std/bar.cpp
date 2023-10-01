#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=52,M=3e5+5;
int n,m,k,e[N][N],ee[N],a,b;
struct road{
    int w,d,a[N];
    inline bool operator <(const road &tp)const{
        if(w^tp.w) return w<tp.w;
        for(int i=1;i<=n;i++) if(a[i]^tp.a[i]) return a[i]<tp.a[i];
    }
}d[N],mi,st[M];
int up[M],t;
ll se[M];
bool vis[N],usd[M];
inline bool dij(int u){
    for(int i=1;i<=n;i++) d[i].w=1e9,d[i].d=0;
    d[u]=(road){};road mi,tp;
    while(!vis[b]){
        u=0;mi.w=1e9-1;
        for(int i=1;i<=n;i++) if(!vis[i]&&d[i]<mi) u=i,mi=d[i];
        if(!u) break;
        vis[u]=1;
        for(int v=1;v<=n;v++) if(e[u][v]&&!vis[v]){
            tp=d[u];tp.w+=e[u][v];tp.a[++tp.d]=v;
            if(tp<d[v]) d[v]=tp;
        }
    }
    return vis[b];
}
inline void spd(road &kp,int ps,ll ss){
    memset(vis,0,n+1);
    int u=kp.a[ps],w=0;
    for(int i=1;i<ps;i++) vis[kp.a[i]]=1,w+=e[kp.a[i]][kp.a[i+1]];
    ss|=1ll<<kp.a[ps+1];
    for(int i=1;i<=n;i++) if((ss>>i)&1) ee[i]=e[u][i],e[u][i]=0;
    if(dij(u)){
        up[++t]=ps;se[t]=ss;
        st[t].w=w+d[b].w;
        st[t].d=ps+d[b].d;
        for(int i=1;i<=ps;i++) st[t].a[i]=kp.a[i];
        for(int i=1;i<=d[b].d;i++) st[t].a[i+ps]=d[b].a[i];
    }
    for(int i=1;i<=n;i++) if((ss>>i)&1) e[u][i]=ee[i];
}
int main(){
    cin>>n>>m>>k;a=1;b=n;
    for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),e[u][v]=w;
    road I=(road){1,1,0,a},mi;spd(I,1,0);
    for(int u=1,v;;u++){
        mi.w=1e9-1;v=0;
        for(int i=1;i<=t;i++) if(!usd[i]&&st[i]<mi) mi=st[i],v=i;
        if(!v) puts("-1"),exit(0);
        usd[v]=1;
        if(u==k){
            printf("%d\n",mi.d);
            for(int i=1;i<=mi.d;i++) printf("%d ",mi.a[i]);
            exit(0);
        }
        for(int i=up[v];i<mi.d;i++) spd(mi,i,i>up[v]?0:se[v]);
    }
}
