#include <bits/stdc++.h>
using namespace std;
const int N=2e4+10,V=(1<<14);
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int tot=1;
stack<int>sta;
int x[N],y[N];
vector<int> End[N];
int ans[N*2];
int dp[16][V];
int siz[N],son[N];
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int id[N];
void dfs2(int u){
    if(son[u]){
        id[son[u]]=id[u];
        dfs2(son[u]);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(id[v]!=-1)continue;
        id[v]=id[u]+1;
        dfs2(v);
    }
}
int tmp[V];
void calc(int u,int fa){
    for(int i:End[u])ans[i]-=dp[id[u]][0];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa||v==son[u])continue;
        for(int j=0;j<V;j++)dp[id[v]][j]=max(dp[id[u]][j],(dp[id[u]][j^x[v]]>=0?dp[id[u]][j^x[v]]+y[v]:-1));
        calc(v,u);
    }
    if(!son[u])return;
    for(int j=0;j<V;j++)tmp[j]=dp[id[u]][j];
    int v=son[u];
    for(int j=0;j<V;j++)dp[id[v]][j]=max(dp[id[u]][j],(tmp[j^x[v]]>=0?tmp[j^x[v]]+y[v]:-1));
    calc(v,u);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    int sum=0;
    sta.push(tot);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        if(s=="ADD"){
            tot++;
            cin>>x[tot]>>y[tot];
            add(sta.top(),tot);
            sta.push(tot);
            sum+=y[tot];
        }
        else{
            sum-=y[sta.top()];
            sta.pop();
        }
        ans[i]=sum;
        End[sta.top()].push_back(i);
    }
    memset(id,-1,sizeof id);
    id[1]=0;
    dfs1(1,0);
    dfs2(1);
    memset(dp,-1,sizeof dp);
    dp[0][0]=0;
    calc(1,0);
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}