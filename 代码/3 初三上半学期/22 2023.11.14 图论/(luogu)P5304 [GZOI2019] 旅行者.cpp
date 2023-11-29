/*
将特殊点分为两个点集A,B
s向A中的所有点连一条边权为0的边。
B中的所有点向t连一条边权为0的边。
然后s与t的最短路就是要求的答案。
我们发现，感兴趣的两个点一定不同。
也就是说，他们的二进制位至少有一位不同
那么我们就能有一个 O(Tnlognlogk) 的做法。
虽然不是最优时间复杂度，但是能过

多测不清空，爆零痛心中
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
    int v,w,nex;
}a[N],tmp1[N];
int first[N],cnt,tmp2[N];
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}

void init(){
    memset(first,0,sizeof(first));
    cnt=0;
}
int dis[N];
bool vis[N];
struct node2{
    int id,w;
    bool operator <(const node2 &b)const {
        return w>b.w;
    }
};
int dij(int s,int t) {
    priority_queue<node2> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,false,sizeof vis);
    dis[s]=0;
    q.push({s,0});
    while(!q.empty()) {
        int u=q.top().id;
        q.pop();
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
    return dis[t];
}
int b[N];
void solve(){
    init();
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    for(int i=1;i<=k;i++) cin>>b[i];
    int ans=1e18;
    for(int i=0;(1<<i)<=k;i++) {
        memcpy(tmp1,a,sizeof a);
        memcpy(tmp2,first,sizeof first);

        int s=n*2+1,t=n*2+2;
        for(int j=1;j<=k;j++) {
            if((j>>i)&1) add(s,b[j],0);
            else add(b[j],t,0);
        }
        ans=min(ans,dij(s,t));
        memcpy(a,tmp1,sizeof tmp1);
        memcpy(first,tmp2,sizeof tmp2);
        for(int j=1;j<=k;j++) {
            if((j>>i)&1) add(b[j],t,0);
            else add(s,b[j],0);
        }
        ans=min(ans,dij(s,t));
        memcpy(a,tmp1,sizeof tmp1);
        memcpy(first,tmp2,sizeof tmp2);
    }
    cout<<ans<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while(T--) solve();
}
