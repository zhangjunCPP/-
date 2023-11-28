#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int now[N],dep[N];
int bfs(int s,int t){
    memcpy(now,first,sizeof(now));
    memset(dep,0,sizeof(dep));
    queue<int> q;
    dep[s]=1;
    now[s]=first[s];
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(a[i].w&&!dep[v]){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dinic(int s,int t,int flow){
    if(s==t) return flow;
    int res=flow;
    for(int i=now[s];i&&res;i=a[i].nex){
        now[s]=i;
        int v=a[i].v;
        if(a[i].w&&dep[v]==dep[s]+1){
            int tmp=dinic(v,t,min(a[i].w,res));
            if(tmp==0) dep[v]=0;
            res-=tmp;
            a[i].w-=tmp;
            a[i^1].w+=tmp;
        }
    }
    return flow-res;
} 
int solve(int s,int t) {
    int ans=0;
    while(bfs(s,t)){
        int tmp;
        while((tmp=dinic(s,t,1e9))) ans+=tmp;
    }
    return ans;
}
int b[N];

bool flag[N];
int tot,prime[N];
void init(){
    for(int i=2;i<=N-10;i++) {
        if(!flag[i])prime[++tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=N-10;j++) {
            flag[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
bool vis[N];
vector<int> G[N];
int sum;
void dfs(int u){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v]) continue;
        if(b[u]&1) {
            if(a[i].w==0) {
                G[sum].push_back(v);
                vis[v]=true;
                dfs(v);
            }
        }
        else {
            if(a[i].w==1) {
                G[sum].push_back(v);
                vis[v]=true;
                dfs(v);
            }
        }
    
    }
}
int main(){
    init();
    int n;
    cin>>n;
    int s=n*10+1,t=n*10+2;
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++) {
        if(b[i]&1) add(s,i,2),add(i,s,0);
        else add(i,t,2),add(t,i,0);
    }    

    for(int i=1;i<=n;i++){
        if(!(b[i]&1)) continue;
        for(int j=1;j<=n;j++){
            if(b[j]&1) continue;
            if(!flag[b[i]+b[j]])add(i,j,1),add(j,i,0);
        }
    }
    int ans=solve(s,t);
    if(ans!=n) {puts("Impossible");return 0;}
    for(int i=1;i<=n;i++) {
        if(vis[i]) continue;
        if(b[i]&1){
            vis[i]=true;
            sum++;
            G[sum].push_back(i);
            dfs(i);
        }
    } 
    cout<<sum<<"\n";
    for(int i=1;i<=sum;i++) {
        cout<<G[i].size()<<" ";
        for(int j:G[i]) cout<<j<<" ";
        cout<<"\n";
    }
    return 0;
}
