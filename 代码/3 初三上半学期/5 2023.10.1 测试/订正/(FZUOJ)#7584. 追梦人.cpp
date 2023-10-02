#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=1e9+7;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}

int dis[2][N];
bool vis[N];
struct node2{
    int id,val;
    bool operator<(const node2 &b) const {
        return val>b.val;
    }
};
void dij(int s,int opt){
    memset(dis[opt],0x3f,sizeof dis[opt]);
    memset(vis,false,sizeof vis);
    priority_queue<node2> q;
    dis[opt][s]=0;
    q.push({s,dis[opt][s]});
    while(!q.empty()){
        node2 now=q.top();
        q.pop();
        if(vis[now.id]) continue;
        vis[now.id]=true;
        for(int i=first[now.id];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[opt][v]>dis[opt][now.id]+a[i].w){
                dis[opt][v]=dis[opt][now.id]+a[i].w;
                q.push({v,dis[opt][v]});
            }
        }
    }
}

int sum[2][N],d[2][N];
bool vis2[N];
void dfs(int u,int fa,int opt){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||dis[opt][v]!=dis[opt][u]+a[i].w) continue;
        if(vis2[i]||opt){
            d[opt][v]--;
            sum[opt][v]=(sum[opt][v]+sum[opt][u])%mod;
            if(d[opt][v]==0) dfs(v,u,opt);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,m,T,k,id;
    cin>>n>>m>>T>>k>>id;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    while(T--){
        int s,t;
        cin>>s>>t;
        dij(s,0);
        dij(t,1);
        memset(sum,0,sizeof sum);
        memset(d,0,sizeof d);
        memset(vis2,false,sizeof vis2);
        for(int i=1;i<=n;i++){
            for(int j=first[i];j;j=a[j].nex){
                int v=a[j].v;
                if(dis[0][i]+dis[1][v]+a[j].w==dis[0][t]){
                    vis2[j]=vis2[j^1]=1;
                    d[0][v]++;
                }
                if(dis[1][v]==dis[1][i]+a[j].w) d[1][v]++;
            }
        }
        sum[0][s]=sum[1][t]=1;
        dfs(s,0,0);
        dfs(t,0,1);
        if(k==0) { cout << sum[0][t] << "\n";continue; }
        int ans=sum[0][t]>1?sum[0][t]:0;
        for(int i=1;i<=n;i++){
            if(sum[0][i]&&i!=t){
                for(int j=first[i];j;j=a[j].nex){
                    int v=a[j].v;
                    if(dis[0][i]+a[j].w+dis[1][v]!=dis[0][t]) {
                        ans=(ans+sum[0][i]*sum[1][v]%mod)%mod;
                    }
                }
            }
        }
        cout<<ans<<"\n";
    }
}
