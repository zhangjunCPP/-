#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int dp[N];
int sum[N][25];
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) sum[i][j]=sum[i-1][j];
        int x;
        cin>>x;
        sum[i][x]++;
    }
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=0;i<(1<<m);i++){
        int tmp=0;
        for(int j=1;j<=m;j++) if(i&(1<<(j-1))) tmp+=sum[n][j];
        for(int j=1;j<=m;j++) {//tmp+1~tmp+sum[n][j]
            if(!(i&(1<<(j-1)))){
                dp[i|(1<<(j-1))]=min(dp[i|(1<<(j-1))],dp[i]+sum[n][j]-(sum[tmp+sum[n][j]][j]-sum[tmp][j]));
            }
        }
    }
    cout<<dp[(1<<m)-1];
}