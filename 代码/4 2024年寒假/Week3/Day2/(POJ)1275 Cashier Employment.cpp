#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dis[N];
bool vis[N];
int sum[N];
bool SPFA(int mid){
    memset(dis,-0x3f,sizeof dis);
    memset(sum,0,sizeof sum);
    memset(vis,false,sizeof vis);
    queue<int> q;
    q.push(0);
    dis[0]=0;
    vis[0]=true;
    sum[0]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]<dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                sum[v]=sum[u]+1;
                if(sum[v]>26)return false;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return true;
}
int r[N];
int s[N];
bool check(int mid){
    memset(first,0,sizeof first);
    cnt=0;
    for(int i=1;i<=24;i++)add(i-1,i,0),add(i,i-1,-s[i]);
    for(int i=8;i<=24;i++)add(i-8,i,r[i]);
    for(int i=1;i<=7;i++)add(i+16,i,r[i]-mid);
    add(0,24,mid),add(24,0,-mid);
    return SPFA(mid);
}
void solve(){
    memset(s,0,sizeof s);
    for(int i=1;i<=24;i++)cin>>r[i];
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        x++;
        s[x]++;
    }
    int L=0,R=n,ans=-1;
    while(L<=R){
        int mid=(L+R)>>1;
        if(check(mid))ans=mid,R=mid-1;
        else L=mid+1;
    }
    if(ans==-1)puts("No Solution");
    else cout<<ans<<"\n";
    return;
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}
