#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct node{
    int v,w,nex;
}a[N*2];
int cnt,first[N];
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dep[N];
void dfs(int u,int fa){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dep[v]=dep[u]+a[i].w;
        dfs(v,u);
    }
}
void init(){
    memset(first,0,sizeof first);
    cnt=0;
}
int pre[N];
int main(){
    int n;
    while(cin>>n){
        init();
        for(int i=2;i<=n;i++){
            int u,w;
            cin>>u>>w;
            add(u,i,w);
            add(i,u,w);
        }
        dep[1]=0;
        dfs(1,0);
        int root1=1;
        for(int i=2;i<=n;i++) if(dep[i]>dep[root1]) root1=i;
        dep[root1]=0;
        dfs(root1,0);
        int root2=1;
        for(int i=1;i<=n;i++) {
            if(dep[i]>dep[root2]) root2=i;
            pre[i]=dep[i];
        }
        dep[root2]=0;
        dfs(root2,0);
        for(int i=1;i<=n;i++) cout<<max(pre[i],dep[i])<<"\n";
    }
}
