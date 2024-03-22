#include <bits/stdc++.h>

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
int siz[N],son[N];
void dfs(int u,int dad){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dep[N];
vector<int> tmp[30];
void dfs2(int u){
    tmp[dep[u]].push_back(u);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(dep[v]||v==son[u])continue;
        dep[v]=dep[u]+1;
        dfs2(v);
    }
    if(son[u]){
        int v=son[u];
        dep[v]=dep[u];
        dfs2(v);
    }
}
pair<int,int> ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    dep[1]=1;
    dfs2(1);
    for(int i=1;i<=20;i++)for(int j=0;j<tmp[i].size();j++)ans[tmp[i][j]]={j+1,i};
    for(int i=1;i<=n;i++)cout<<ans[i].first<<" "<<ans[i].second<<"\n";
}