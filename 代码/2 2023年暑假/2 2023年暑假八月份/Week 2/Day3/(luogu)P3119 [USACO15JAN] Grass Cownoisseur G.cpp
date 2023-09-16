#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;

vector<int> G[N];

int dfn[N],low[N],idx;
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
    dfn[u]=low[u]=++idx;
    s.push(u);
    vis[u]=true;
    for(int v:G[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        ++tot;
        while (s.top()!=u){
            scc[s.top()]=tot;
            vis[s.top()]=false;
            s.pop();
        }
        scc[s.top()]=tot;
        vis[s.top()]=false;
        s.pop();
    }
}
int siz[N];
vector<int> G2[N];
vector<int> G3[N];
bool flag[N];
int dis1[N];
void spfa1(int s){
    for(int i=1;i<=tot;i++) flag[i]= false;
    queue<int> q;
    q.push(s);
    dis1[s]=siz[s];
    flag[s]=true;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        flag[now]=false;
        for(int v:G2[now]){
            if(dis1[v]<dis1[now]+siz[v]){
                dis1[v]=dis1[now]+siz[v];
                if(!flag[v]) q.push(v),flag[v]=true;
            }
        }
    }
}
int dis2[N];
void spfa2(int s){
    for(int i=1;i<=tot;i++) flag[i]= false;
    queue<int> q;
    q.push(s);
    dis2[s]=siz[s];
    flag[s]=true;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        flag[now]=false;
        for(int v:G3[now]){
            if(dis2[v]<dis2[now]+siz[v]){
                dis2[v]=dis2[now]+siz[v];
                if(!flag[v]) q.push(v),flag[v]=true;
            }
        }
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++) siz[scc[i]]++;
    if(tot==1) {
        cout<<siz[1];
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j:G[i]){
            if(scc[i]!=scc[j]){
                G2[scc[i]].push_back(scc[j]);
                G3[scc[j]].push_back(scc[i]);
            }
        }
    }
    spfa1(scc[1]);
    spfa2(scc[1]);
    int ans=-1;
    for(int i=1;i<=tot;i++){
        for(int j:G3[i]){
            if(dis1[i]&&dis2[j]) ans=max(ans,dis1[i]+dis2[j]-siz[scc[1]]);
        }
    }
    cout<<ans;
}