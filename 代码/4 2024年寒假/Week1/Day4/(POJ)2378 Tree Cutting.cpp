#include <iostream>
#define ll long long
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
ll siz[N];
bool flag[N];
void dfs(int u,int fa){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>n/2) flag[u]=true;
    }
    if(n-siz[u]>n/2) flag[u]=true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    bool tmp=true;
    for(int i=1;i<=n;i++)if(!flag[i]) cout<<i<<"\n",tmp=false;
    if(tmp) cout<<"NONE";
}