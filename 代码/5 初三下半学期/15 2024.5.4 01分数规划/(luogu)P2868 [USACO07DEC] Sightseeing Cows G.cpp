#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
struct node{
    int v;
    double w;
    int nex;
}a[N];
int first[N],cnt;
void add(int u,int v,double w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
double dis[N];
bool vis[N];
int sum[N];
int n,m;
bool SPFA(){
    queue<int> q;
    for(int i=0;i<=n;i++)dis[i]=0,sum[i]=1,vis[i]=true,q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]<dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                sum[v]=sum[u]+1;
                if(sum[v]>n)return true;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return false;
}
int f[N];
int u[N],v[N],w[N];
bool check(double mid){
    memset(first,0,sizeof first);
    cnt=0;
    for(int i=1;i<=m;i++)add(u[i],v[i],1.0*(f[u[i]]-mid*w[i]));
    return SPFA();
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>f[i];
    for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>w[i];
    double l=0,r=1e5+10;
    while(r-l>1e-4){
        double mid=(l+r)/2;
        if(check(mid))l=mid;
        else r=mid;
    }
    printf("%.2lf",l);
    return 0;
}