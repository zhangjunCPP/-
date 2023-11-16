#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int w[N];
int dep[N],fa[N][25];
bitset<50005>val[N];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa[u][0]=dad;
    val[u]=val[dad];
    val[u][w[u]]=val[u][w[u]]^1;
    for(int i=1;i<25;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=24;i>=0;i--)if(dep[fa[u][i]]>=dep[v])u=fa[u][i];
    if(u==v)return u;
    for(int i=24;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int tot;
map<int,int> mp;
signed main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) {
        cin>>w[i];
        int tmp=1;
        for(int j=2;j*j<=w[i];j++) {
            if(w[i]%j==0){
                int cnt=0;
                while(w[i]%j==0){
                    w[i]/=j;
                    cnt++;
                }
                if(cnt&1) tmp=tmp*j;
            }
        }
        tmp=tmp*w[i];
        if(!mp.count(tmp)) mp[tmp]=++tot;
        w[i]=mp[tmp];
    }
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    while(q--){
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        int dis=dep[x]+dep[y]-2*dep[lca];
        auto tmp=val[x]^val[y];
        tmp[w[lca]]=tmp[w[lca]]^1;
        if(tmp.count()==dis+1) puts("No");
        else puts("Yes");
    }
    return 0;
}
