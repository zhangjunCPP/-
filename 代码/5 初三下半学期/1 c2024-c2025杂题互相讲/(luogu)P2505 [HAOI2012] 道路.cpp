#include <bits/stdc++.h>

using namespace std;
const int N=2e3+10,M=5e3+10,mod=1e9+7;
int n,m;
struct node{
    int v,w,nex;
}a[M];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
struct node2{
    int id,val;
    bool operator<(const node2&oth)const{return val>oth.val;}
};
int dis[N];
bool vis[N];
priority_queue<node2>q;
void dij(int s){
    memset(dis,0x3f,sizeof dis);
    memset(vis,false,sizeof vis);
    dis[s]=0;
    q.push({s,0});
    while(!q.empty()){
        int u=q.top().id;
        q.pop();
        if(vis[u])continue;
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
bool flag[M];
int deg[N];
int sum1[N],sum2[N];
int Q[M];
void top_sort(int s){
    memset(flag,false,sizeof flag);
    memset(deg,0,sizeof deg);
    memset(sum1,0,sizeof sum1);
    memset(sum2,0,sizeof sum2);
    sum1[s]=1;
    for(int i=1;i<=n;i++){
        for(int j=first[i];j;j=a[j].nex){
            int v=a[j].v;
            if(dis[v]==dis[i]+a[j].w)flag[j]=true;
        }
    }
    for(int i=1;i<=m;i++)if(flag[i])deg[a[i].v]++;
    int tot=0;
    Q[++tot]=s;
    for(int i=1;i<=tot;i++){
        int u=Q[i];
        for(int j=first[u];j;j=a[j].nex){
            if(!flag[j])continue;
            int v=a[j].v;
            sum1[v]=(sum1[v]+sum1[u])%mod;
            deg[v]--;
            if(!deg[v])Q[++tot]=v;
        }
    }
    for(int i=tot;i;i--){
        int u=Q[i];
        sum2[u]++;
        for(int j=first[u];j;j=a[j].nex){
            if(!flag[j])continue;
            int v=a[j].v;
            sum2[u]=(sum2[u]+sum2[v])%mod;
        }
    }
}
int ans[M];
void solve(int s){
    dij(s);
    top_sort(s);
    for(int i=1;i<=n;i++)for(int j=first[i];j;j=a[j].nex){
            if(flag[j])ans[j]=(ans[j]+sum1[i]*sum2[a[j].v])%mod;
        }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    for(int i=1;i<=n;i++)solve(i);
    for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}