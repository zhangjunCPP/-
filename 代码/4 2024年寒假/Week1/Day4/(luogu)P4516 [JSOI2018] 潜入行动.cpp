#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;

int k;
vector<int> G[N];
int dp[N][105][2][2];
int tmp[105][2][2];
int siz[N];
void dfs(int u,int fa){
    siz[u]=1;
    dp[u][0][0][0]=1;
    dp[u][1][1][0]=1;
    for(int v:G[u]){
        if(v==fa) continue;
        dfs(v,u);
        int Min=min(siz[u]+siz[v],k);
        for(int i=0;i<=siz[u];i++)
            for(int j=0;j<=siz[v]&&i+j<=Min;j++)
                for(int p1=0;p1<2;p1++)for(int q1=0;q1<2;q1++)
                        for(int p2=0;p2<2;p2++)for(int q2=0;q2<2;q2++)
                                if(q2|p1)tmp[i+j][p1][q1|p2]=(tmp[i+j][p1][q1|p2]+1ll*dp[u][i][p1][q1]*dp[v][j][p2][q2]%mod)%mod;
        for(int i=0;i<=Min;i++){
            dp[u][i][0][0]=tmp[i][0][0];
            dp[u][i][0][1]=tmp[i][0][1];
            dp[u][i][1][0]=tmp[i][1][0];
            dp[u][i][1][1]=tmp[i][1][1];
        }
        for(int i=0;i<=Min;i++)tmp[i][0][0]=tmp[i][0][1]=tmp[i][1][0]=tmp[i][1][1]=0;
        siz[u]=Min;
    }
}

int n;
int main(){
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0);
    cout<<(dp[1][k][0][1]+dp[1][k][1][1])%mod;
}