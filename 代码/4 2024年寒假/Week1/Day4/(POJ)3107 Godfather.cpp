#include <cstdio>
#include <iostream>
using namespace std;
const int N=2e5+10;
struct node{
    int v,nex;
}a[N];
int cnt,first[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int n;
int siz[N];
bool flag[N];
int Max[N];
void dfs(int u,int fa){
    siz[u]=1;
    Max[u]=-1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        Max[u]=max(Max[u],siz[v]);
    }
    Max[u]=max(Max[u],n-siz[u]);
    if(Max[u]<=n/2) flag[u]=true;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) if(flag[i]) printf("%d ",i);
}