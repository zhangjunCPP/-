#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],tot;
stack<int> s;
bool vis[N];
int scc[N],col;
void Tarjan(int u){
    low[u]=dfn[u]=++tot;
    s.push(u);
    vis[u]=true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        scc[u]=++col;
        while(s.top()!=u){
            scc[s.top()]=col;
            vis[s.top()]=false;
            s.pop();
        }
        s.pop();
        vis[u]=false;
    }
}
int p[N],q[N];
int deg[N];
int ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++)cin>>q[i];
    for(int i=1;i<n;i++)add(p[i],p[i+1]),add(q[i],q[i+1]);
    for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
    if(col<k){puts("NO");return 0;}
    puts("YES");
    memset(first,0,sizeof first);
    cnt=0;
    for(int i=1;i<n;i++){
        if(scc[p[i]]!=scc[p[i+1]])add(scc[p[i]],scc[p[i+1]]),deg[scc[p[i+1]]]++;
        if(scc[q[i]]!=scc[q[i+1]])add(scc[q[i]],scc[q[i+1]]),deg[scc[q[i+1]]]++;
    }
    queue<int> q;
    for(int i=1;i<=col;i++)if(!deg[i])q.push(i);
    int tmp=0;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        ans[now]=++tmp;
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            --deg[v];
            if(!deg[v])q.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        putchar(ans[scc[i]]<=26?ans[scc[i]]+'a'-1:'z');
    }
}