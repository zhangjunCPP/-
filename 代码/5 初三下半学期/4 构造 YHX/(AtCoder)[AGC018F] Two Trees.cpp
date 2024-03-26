#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n;
struct node{
    int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int deg1[N],deg2[N];
bool vis[N];
int ans[N];
void dfs(int u){
    for(int i=first[u];i;i=first[u]){
        first[u]=a[i].nex;
        int v=a[i].v;
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        if(abs(u-v)==n)ans[min(u,v)]=u<v?1:-1;
        dfs(v);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==-1)add(0,i),add(i,0),deg1[i]++,deg1[0]++;
        else add(x,i),add(i,x),deg1[i]++,deg1[x]++;
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==-1)add(0,i+n),add(i+n,0),deg2[i]++,deg2[0]++;
        else add(x+n,i+n),add(i+n,x+n),deg2[i]++,deg2[x]++;
    }
    for(int i=1;i<=n;i++){
        if(deg1[i]%2!=deg2[i]%2) {
            puts("IMPOSSIBLE");
            return 0;
        }
        if(deg1[i]&1)add(i,i+n),add(i+n,i);
    }
    puts("POSSIBLE");
    dfs(0);
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    return 0;
}