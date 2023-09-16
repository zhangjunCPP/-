#include <bits/stdc++.h>

using namespace std;
const int N=200005;

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

bool vis2[N];
vector<int> G2[N];
int in[N];
int siz[N];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++) siz[scc[i]]++;

    for(int u=1;u<=n;u++){
        for(int v:G[u]){
            if(scc[u]==scc[v]||vis2[scc[v]]) continue;
            G2[scc[u]].push_back(scc[v]);
            in[scc[v]]++;
            vis2[scc[v]]=true;
        }
        for(int v:G[u])vis2[scc[v]]= false;
    }

    bool flag=true;
    int ans=0;
    for(int i=1;i<=tot;i++){
        if(in[i]==0) ans++;
        if(in[i]||siz[i]>1) continue;
        if(flag){
            bool flag2=true;
            for(int j:G2[i]){
                if(in[j]<=1) {
                    flag2= false;
                    break;
                }
            }
            if(flag2) ans--,flag=false;
        }
    }
    printf("%.6lf",(double)(n-ans)/n);
}