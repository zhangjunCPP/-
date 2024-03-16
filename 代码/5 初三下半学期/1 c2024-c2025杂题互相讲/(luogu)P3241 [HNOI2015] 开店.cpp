#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int x[N];
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int rt,Min;
int siz[N];
bool vis[N];
void get_rt(int u,int fa,int sum){
    siz[u]=1;
    int Max=0;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||vis[v])continue;
        get_rt(v,u,sum);
        siz[u]+=siz[v];
        Max=max(Max,siz[v]);
    }
    Max=max(Max,sum-siz[u]);
    if(Min>Max)Min=Max,rt=u;
}
struct node2{
    int id,dis,opt;
};
vector<node2> G[N];

int dep[N];
struct node3{
    int val,s1,s2;
    bool operator<(const node3&oth)const{return val<oth.val;}
};
vector<node3> ans[N][3];
void dfs(int u,int fa,int id,int opt){
    G[u].push_back({id,dep[u],opt});
    ans[id][opt].push_back({x[u],1,dep[u]});
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||vis[v])continue;
        dep[v]=dep[u]+a[i].w;
        dfs(v,u,id,opt);
    }
}
void solve(int u){
    Min=0x3f3f3f3f;
    rt=0;
    get_rt(u,0,siz[u]);
    vis[rt]=true;
    G[rt].push_back({rt,0,-1});
    if(siz[u]==1)return;
    int tmp=0;
    for(int i=first[rt];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v])continue;
        dep[v]=a[i].w;
        dfs(v,0,rt,tmp);
        ans[rt][tmp].push_back({0x3f3f3f3f,0,0});
        sort(ans[rt][tmp].begin(), ans[rt][tmp].end());
        for(int j=ans[rt][tmp].size()-2;j>=0;j--){
            ans[rt][tmp][j].s1+=ans[rt][tmp][j+1].s1;
            ans[rt][tmp][j].s2+=ans[rt][tmp][j+1].s2;
        }
        tmp++;
    }
    for(int i=first[rt];i;i=a[i].nex){
        int v=a[i].v;
        if(vis[v])continue;
        solve(v);
    }
}
int get_ans(int u,int l,int r){
    int sum=0;
    for(auto now:G[u]){
        int id=now.id;
        for(int i=0;i<=2;i++){
            if(i==now.opt||ans[id][i].empty())continue;
            auto L=lower_bound(ans[id][i].begin(), ans[id][i].end(),node3{l,0,0});
            auto R=upper_bound(ans[id][i].begin(), ans[id][i].end(),node3{r,0,0});
            sum+=now.dis*(L->s1-R->s1)+(L->s2-R->s2);
        }
        if(x[id]>=l&&x[id]<=r)sum+=now.dis;
    }
    return sum;
}
signed main(){
    int n,q,A;
    cin>>n>>q>>A;
    for(int i=1;i<=n;i++)cin>>x[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    Min=0x3f3f3f3f;
    rt=0;
    get_rt(1,0,n);
    solve(rt);
    int lastans=0;
    while(q--){
        int u,l,r;
        cin>>u>>l>>r;
        l=(l+lastans)%A;
        r=(r+lastans)%A;
        if(r<l)swap(l,r);
        lastans= get_ans(u,l,r);
        cout<<lastans<<"\n";
    }
}