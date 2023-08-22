#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
const int INF=3e9;
using namespace std;
const int N=1e7;
int s,t;
struct Node{
    int v,w,nex;
}a[N];
int cnt=1,first[N];
void add(int u,int v,int w){
    a[++cnt]=Node{v,w,first[u]};
    first[u]=cnt;
}
void insert(int u,int v,int w){
    add(u,v,w),add(v,u,0);
}
int now[N];
int d[N];
int bfs(){
    memset(d, false,sizeof d);
    queue<int> q;
    q.push(s);
    d[s]=1;
    now[s]=first[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!d[v]){
                q.push(v);
                now[v]=first[v];
                d[v]=d[u]+1;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int x,int val){
    if(x==t) return val;
    int have=val;
    for(int i=now[x];i&&have;i=a[i].nex){
        now[x]=i;
        int v=a[i].v;
        if(a[i].w&&d[v]==d[x]+1){
            int tmp= dinic(v,min(a[i].w,have));
            if(!tmp) d[v]=0;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
            have-=tmp;
        }
    }
    return val-have;
}

int n,m,k;
int f(int i,int j){return (i-1)*m+j;}
signed main(){
    cin>>n>>m>>k;
    s=100*n+5;
    t=s+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            int y=(~x?200-x:INF);
            if(j==1) insert(s,f(i,j),INF);
            if(j==m) insert(f(i,j),t,y);
            else insert(f(i,j),f(i,j+1),y);
        }
    }
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;
        for(int j=1;j<m;j++)insert(f(x,j),f(y,j+1),INF);
        insert(f(x,m),t,INF);
    }
    int ans=0;
    while(bfs()){
        int tmp;
        while(tmp= dinic(s,MAX)) ans+=tmp;
    }
    printf("%.2lf",1.0*(200*n-ans)/n);
    return 0;
}