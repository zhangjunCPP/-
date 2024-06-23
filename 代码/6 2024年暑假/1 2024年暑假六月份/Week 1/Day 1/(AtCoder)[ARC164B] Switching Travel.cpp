#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int fa[N];
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
void merge(int u,int v){
    int fu=find(u),fv=find(v);
    if(fu!=fv)fa[fu]=fv;
}
int u[N],v[N];
int col[N];
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>u[i]>>v[i];
    for(int i=1;i<=n;i++)cin>>col[i];
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)if(col[u[i]]!=col[v[i]])merge(u[i],v[i]);
    bool flag=false;
    for(int i=1;i<=m;i++)if(col[u[i]]==col[v[i]]&&find(u[i])==find(v[i]))flag=true;
    if(flag)puts("Yes");
    else puts("No");
}