#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e15;
struct node{
    int v,w,nex,val;
}a[N];
int first[N],cnt=1;
int now[N];
void add(int u,int v,int w,int val){
    a[++cnt]={v,w,first[u],val};
    first[u]=cnt;
}
void insert(int u,int v,int w,int val){
    add(u,v,w,val);
    add(v,u,0,-val);
}
int dis[N];
bool vis[N];
bool spfa(int s,int t){
    queue<int> q;
    memset(dis,0x3f,sizeof dis);
    memset(vis,false,sizeof vis);
    dis[s]=0;
    q.push(s);
    vis[s]=true;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&dis[v]>dis[u]+a[i].val){
                now[v]=first[v];
                dis[v]=dis[u]+a[i].val;
                if(!vis[v]) q.push(v),vis[v]=true;
            }
        }
    }
    return dis[t]!=dis[N-1];
}
int dinic(int s,int flow,int t){
    if(s==t) return flow;
    vis[s]=true;
    int have=flow;
    for(int i=now[s];i&&have;i=a[i].nex){
        now[s]=i;
        int v=a[i].v;
        if(!vis[v]&&a[i].w&&dis[v]==dis[s]+a[i].val){
            int tmp=dinic(v,min(have,a[i].w),t);
            if(tmp==0) dis[v]=-1;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    vis[s]=false;
    return flow-have;
}

pair<int,int> solve(int s,int t,int n){
    int ans1=0,ans2=0;
    while(spfa(s,t)){
        int tmp;
        while((tmp=dinic(s,1e18,t))){ans1+=tmp,ans2+=tmp*dis[t];}
    }
    return {ans1,ans2};
}
int x[N],y[N],v[N];
int x_max[N],x_min[N];
int y_max[N],y_min[N];
void init(){
    cnt=1;
    memset(first,0,sizeof first);
}
int calc(int n,int k){
    init();
    int s=0;
    int t=2*k+2*n+1;
    for(int i=1;i<=k;i++){
        insert(s,i,1,0);
        insert(k+2*n+i,t,1,0);
    }
    for(int i=1;i<=n;i++){
        insert(k+i,k+i+n,1,-v[i]);
        for(int j=1;j<=k;j++){
            if(x[i]>=x_min[j]&&x[i]<=x_max[k-j+1])insert(j,i+k,1,0);
            if(y[i]>=y_min[j]&&y[i]<=y_max[k-j+1])insert(i+k+n,k+2*n+j,1,0);
        }
    }
    auto ans=solve(s,t,n);
    return -ans.second;
}
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>x[i]>>y[i]>>v[i];
    int m;
    cin>>m;
    memset(x_max,0x3f,sizeof x_max);
    memset(y_max,0x3f,sizeof y_max);
    for(int i=1;i<=m;i++){
        char ch;
        int u,v;
        cin>>ch>>u>>v;
        v++;
        if(ch=='L')x_min[v]=max(x_min[v],u+1);
        else if(ch=='R')x_max[v]=min(x_max[v],u-1);
        else if(ch=='D')y_min[v]=max(y_min[v],u+1);
        else if(ch=='U')y_max[v]=min(y_max[v],u-1);
    }
    for(int i=1;i<=n;i++){
        x_min[i]=max(x_min[i],x_min[i-1]);
        x_max[i]=min(x_max[i],x_max[i-1]);
        y_min[i]=max(y_min[i],y_min[i-1]);
        y_max[i]=min(y_max[i],y_max[i-1]);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,calc(n,i));
    // calc(n,1);
    cout<<ans;
}