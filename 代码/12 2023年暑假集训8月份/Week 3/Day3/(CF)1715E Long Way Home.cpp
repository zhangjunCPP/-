#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
    int v,nex,w;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,first[u],w};
    first[u]=cnt;
}
bool vis[N];
int dis[N];
struct node2{
    int id,val;
    bool operator<(const node2 &b) const{return val>b.val;}
};
priority_queue<node2> q;
void dij(){
    memset(vis,0,sizeof vis);
    while(!q.empty()){
        node2 now=q.top();
        q.pop();
        int u=now.id;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]>dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                q.push({v,dis[v]});
            }
        }
    }
}
int dp[N];
int X(int i){return i;}
int Y(int i){return dp[i]+i*i;}
double slope(int i,int j){
    return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}
int qq[N],l,r;
signed main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }

    memset(dis,0x3f,sizeof dis);
    q.push({1,0});
    dis[1]=0;
    dij();
    while(k--){
        l=1;r=1;
        qq[l]=0;
        for(int i=1;i<=n;i++) dp[i]=dis[i];
        for(int i=1;i<=n;i++){
            while(l<r&&slope(qq[r-1],qq[r])>slope(qq[r],i)) --r;
            qq[++r]=i;
        }
        for(int i=1;i<=n;i++) {
            while (l<r&&slope(qq[l],qq[l+1])<2.0*i) ++l;
            int j=qq[l];
            if(dis[i]>dp[j]+(i-j)*(i-j)){
                dis[i]=dp[j]+(i-j)*(i-j);
                q.push({i,dis[i]});
            }
        }
        dij();
    }
    for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
}
