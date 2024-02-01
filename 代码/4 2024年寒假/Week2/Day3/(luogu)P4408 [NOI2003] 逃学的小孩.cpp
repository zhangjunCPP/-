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
int dis1[N],dis2[N];
void dfs(int u,int dad,int dis[]){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dis[v]=dis[u]+a[i].w;
        dfs(v,u,dis);
    }
}
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0,dis1);
    int rt1=1;
    for(int i=2;i<=n;i++) if(dis1[i]>dis1[rt1]) rt1=i;
    dis1[rt1]=0;
    dfs(rt1,0,dis1);
    int rt2=1;
    for(int i=2;i<=n;i++) if(dis1[i]>dis1[rt2]) rt2=i;
    dis2[rt2]=0;
    dfs(rt2,0,dis2);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(i==rt1||i==rt2) continue;
        ans=max(ans,dis1[rt2]+min(dis1[i],dis2[i]));
    }
    cout<<ans;

}