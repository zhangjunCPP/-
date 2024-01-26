#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
int a[N];
int dp[N][N],w[N][N];
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=n;i++) dp[i][i]=1,w[i][i]=a[i];
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                if(dp[i][k]==1&&dp[k+1][j]==1&&w[i][k]==w[k+1][j]){
                    dp[i][j]=1;
                    w[i][j]=w[i][k]+1;
                    break;
                }
            }
        }
    }
    cout<<dp[1][n];
}