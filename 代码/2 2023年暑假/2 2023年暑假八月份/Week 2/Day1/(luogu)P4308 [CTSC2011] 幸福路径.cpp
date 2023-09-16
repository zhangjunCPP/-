#include <bits/stdc++.h>

using namespace std;
double dp[1005][1005];
double dis[1005][1005];
int n,m;
int s;
double p;
double val[1005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=-0x3f3f3f3f;
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=n;i++) cin>>val[i];
    cin>>s>>p;
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        dis[u][v]=val[v]*p;
    }
    for(;p>1e-10;p*=p){
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=-0x3f3f3f3f;
        for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=max(dp[i][j],dis[i][k]+dis[k][j]*p);
        memcpy(dis,dp,sizeof dp);
    }
    double ans=-0x3f3f3f3f;
    for(int i=1;i<=n;i++) ans=max(ans,dis[s][i]);
    printf("%.1lf",ans+val[s]);

}