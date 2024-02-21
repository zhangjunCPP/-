#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
struct node{
    int v,w,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dis[N];
int fa[N];
bool vis[N];
void dfs(int u,int dad){
    fa[u]=dad;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad||vis[v]) continue;
        dis[v]=dis[u]+a[i].w;
        dfs(v,u);
    }
}
signed main(){
    int n,s;
    cin>>n>>s;
    for(int i=1;i<n;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0);
    int rt1=1;
    for(int i=2;i<=n;i++) if(dis[i]>dis[rt1]) rt1=i;
    dis[rt1]=0;
    dfs(rt1,0);
    int rt2=1;
    for(int i=2;i<=n;i++) if(dis[i]>dis[rt2]) rt2=i;
    int ans=0x3f3f3f3f;
    for(int i=rt2,j=rt2;i;i=fa[i]){
        while(dis[j]-dis[i]>s) j=fa[j];
        int tmp=max(dis[i],dis[rt2]-dis[j]);
        ans=min(ans,tmp);
    }
    for(int i=rt2;i;i=fa[i]) vis[i]=true;
    for(int i=rt2;i;i=fa[i]) {
        dis[i]=0;
        dfs(i,fa[i]);
    }
    for(int i=1;i<=n;i++)ans=max(ans,dis[i]);
    cout<<ans;
}