#include<bits/stdc++.h>
#define ll long long
#define pli pair<ll,int>
#define x first
#define y second
using namespace std;
const int N=2e5+10,mod=1e9+7;
int n,m,T,k;
int h[N],e[2*N],ne[2*N],w[2*N],idx;
ll d[2][N];
priority_queue<pli>q;
bool vis[N],vis2[2*N];
int cnt[2][N],du[2][N];
void add(int a,int b,int c)
{
    e[idx]=b;
    w[idx]=c;
    ne[idx]=h[a];
    h[a]=idx++;
}
void dijk(int s,int op)
{
    memset(d[op],0x3f,sizeof d[op]);
    memset(vis,0,sizeof vis);
    d[op][s]=0;
    q.push({0,s});
    while(!q.empty())
    {
        pli t=q.top();
        q.pop();
        int u=t.y;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=h[u];i!=-1;i=ne[i])
        {
            int v=e[i];
            if(d[op][v]>d[op][u]+w[i])
            {
                d[op][v]=d[op][u]+w[i];
                q.push({-d[op][v],v});
            }
        }
    }
}
void dfs(int u,int op,int f)
{
    for(int i=h[u];i!=-1;i=ne[i])
        if(vis2[i]||op)
        {
            int v=e[i];
            if(v==f||d[op][v]!=d[op][u]+w[i])continue;
            du[op][v]--;
            cnt[op][v]+=cnt[op][u],cnt[op][v]%=mod;
            if(du[op][v]==0)dfs(v,op,u);
        }
}
int main()
{
    freopen("dream.in","r",stdin);
    freopen("dream.out","w",stdout);
    int id;
    scanf("%d%d%d%d%d",&n,&m,&T,&k,&id);
    memset(h,-1,sizeof h);
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);add(b,a,c);
    }
    while(T--)
    {
        memset(vis2,0,sizeof vis2);
        memset(cnt,0,sizeof cnt);
        memset(du,0,sizeof du);
        int s,t;
        scanf("%d%d",&s,&t);
        dijk(s,0),dijk(t,1);
        for(int u=1;u<=n;u++)
            for(int i=h[u];i!=-1;i=ne[i])
            {
                int v=e[i];
                if(d[0][u]+w[i]+d[1][v]==d[0][t])
                    vis2[i]=vis2[i^1]=1,du[0][v]++;
                if(w[i]+d[1][u]==d[1][v])du[1][v]++;
            }
        cnt[0][s]=cnt[1][t]=1;
        dfs(s,0,0);dfs(t,1,0);
        if(k==0)printf("%d\n",cnt[0][t]);
        else
        {
            int res=(cnt[0][t]>1?cnt[0][t]:0);
            for(int u=1;u<=n;u++)
            if(cnt[0][u]&&u!=t)
            {
                for(int i=h[u];i!=-1;i=ne[i])
                {
                    int v=e[i];
                    if(d[0][u]+w[i]+d[1][v]!=d[0][t])
                        res=(res+1ll*cnt[0][u]*cnt[1][v])%mod;
                }
            }
            printf("%d\n",res);
        }
    }
    return 0;
}

