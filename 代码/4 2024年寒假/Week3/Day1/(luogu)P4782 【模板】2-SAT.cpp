#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
struct node{int v,nex;}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N];
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
    dfn[u]=low[u]=++tot;
    s.push(u);
    vis[u]=true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])low[u]=min(low[u],dfn[v]);
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
//1~n:true n+1~2n:false
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,vu,v,vv;
        cin>>u>>vu>>v>>vv;
        add(u+n*vu,v+n*(!vv));
        add(v+n*vv,u+n*(!vu));
    }
    for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n]){puts("IMPOSSIBLE");return 0;}
    cout<<"POSSIBLE\n";
    for(int i=1;i<=n;i++)cout<<(scc[i]<scc[i+n])<<" ";
}