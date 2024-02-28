#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
    deg[v]++;
}
int n;
int siz[N],Max[N];
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dfs1(v,u);
        Max[u]=max(Max[u],siz[v]);
        siz[u]+=siz[v];
    }
    Max[u]=max(Max[u],n-siz[u]);
}
int rt;
unordered_multiset<int> S[N];
void dfs2(int u,int fa){
    S[u].insert(fa==rt?deg[u]-1:deg[u]);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dfs2(v,u);
        for(int tmp:S[v])S[u].insert(tmp);
    }
}
int tmp[N],tot;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++)if(Max[i]*2<=n)tmp[++tot]=i;
    for(int i=1;i<=tot;i++){
        int now=tmp[i];
        rt=now;
        dfs2(now,0);
        int ans=0;
        bool flag=true;
        for(int j=first[now];j;j=a[j].nex){
            int v=a[j].v;
            ans++;
            if(S[v]!=S[a[first[now]].v])flag=false;
        }
        if(flag){
            cout<<ans;
            return 0;
        }
        for(int j=1;j<=n;j++)S[j].clear();
    }
    cout<<"-1";
    return 0;
}