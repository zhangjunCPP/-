#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e6+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int s[N];
int d[N];

int dis[N];
bool vis[N];
struct node2{
    int id,val;
    bool operator<(const node2 &b) const {
        return val>b.val;
    }
};
    int n,m,k;
void dij(int s){
    memset(dis,0x3f,sizeof dis);
    priority_queue<node2> q;
    dis[s]=0;
    q.push({s,dis[s]});
    while(!q.empty()){
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
signed main(){
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++)cin>>s[i];

    bool flag=true;
    for(int i=1;i<=n;i++){
        cin>>d[i];
        if(d[i]!=0) flag=false;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    if(flag) {
        dij(1);
        int ans=0x3f3f3f3f;
        for(int i=1;i<=k;i++)ans=min(ans,dis[s[i]]);
        cout<<ans;
        return 0;
    }
    else{
        cout<<"-1";
        return 0;
    }

}
/*
直接打暴力。
对于d全为0的情况，直接一个最段路完事

---------

感觉像一个博弈论？
Alice最初在1号点，他想要走到出口，Bob每次可以选择d_i条边使Alice不能走。
两者均以最优策略行动，问谁获胜。
若Alice获胜，输出最短时间。
否则输出-1。

--------

不管了，其他的全输出-1
*/
