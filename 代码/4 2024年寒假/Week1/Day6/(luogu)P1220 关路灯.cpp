#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=50+10;
int a[N],sum[N];
int dp[N][N][2];
signed main(){
    int n,c;
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        int x;
        cin>>a[i]>>x;
        sum[i]=sum[i-1]+x;
    }
    memset(dp,0x3f,sizeof dp);
    dp[c][c][0]=dp[c][c][1]=0;
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            dp[i][j][0]=min(dp[i+1][j][0]+(sum[n]-(sum[j]-sum[i]))*(a[i+1]-a[i]),dp[i+1][j][1]+(sum[n]-(sum[j]-sum[i]))*(a[j]-a[i]));
            dp[i][j][1]=min(dp[i][j-1][0]+(sum[n]-(sum[j-1]-sum[i-1]))*(a[j]-a[i]),dp[i][j-1][1]+(sum[n]-(sum[j-1]-sum[i-1]))*(a[j]-a[j-1]));
        }
    }
    cout<<min(dp[1][n][0],dp[1][n][1]);
}