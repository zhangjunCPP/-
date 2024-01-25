#include<bits/stdc++.h>
#define int long long
const int N=13;
int w[N][N];
int sum[(1<<N)][(1<<N)];
int dp[N][(1<<N)];
using namespace std;
signed main(){
    int n,m;
    cin>>n>>m;
    memset(w,0x3f,sizeof w);
    memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=m;i++){
        int u,v,val;
        cin>>u>>v>>val;
        w[u][v]=w[v][u]=min(w[u][v],val);
    }
    for(int x=1;x<(1<<n);x++)
        for(int y=(x-1)&x;y;y=(y-1)&x)
            for(int i=1;i<=n;i++)
                if( ((x>>(i-1))&1) && !((y>>(i-1))&1) ){
                    int Min=0x7fffffff;
                    for(int j=1;j<=n;j++)if((y>>(j-1))&1)Min=min(Min,w[i][j]);
                    sum[y][x]+=Min;
                }
    for(int i=0;i<n;i++)dp[1][(1<<i)]=0;
    for(int i=2;i<=n;i++)for(int x=1;x<(1<<n);x++)for(int y=(x-1)&x;y;y=(y-1)&x)dp[i][x]=min(dp[i][x],dp[i-1][y]+sum[y][x]*(i-1));
    int ans=0x7fffffff;
    for(int i=1;i<=n;i++)ans=min(ans,dp[i][(1<<n)-1]);
    cout<<ans;
    return 0;
}