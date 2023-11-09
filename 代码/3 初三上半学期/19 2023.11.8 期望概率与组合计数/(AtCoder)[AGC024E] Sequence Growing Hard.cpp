#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=300+10;
int n,k,mod;
int C[N][N];
int sum[N][N];
void init(){
    C[0][0]=1;
    for(int i=1;i<N;i++) C[i][0]=C[i][i]=1;
    for(int i=1;i<N;i++)for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    for(int i=1;i<N;i++)for(int j=1;j<=i;j++)for(int k=i-j+1;k<=i;k++) sum[i][j]=(sum[i][j]+C[k-1][i-j])%mod;
}
int dp[N][N];
signed main(){
    cin>>n>>k>>mod;
    init();
    dp[0][0]=1;
    for(int j=1;j<=k;j++) {
        dp[0][j]=1;
        for(int i=1;i<=n;i++) {
            for(int k=1;k<=i;k++)dp[i][j]=(dp[i][j]+dp[k-1][j-1]%mod*dp[i-k][j]%mod*sum[i][k]%mod)%mod;
            dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
        }
    }
    cout<<dp[n][k]<<endl;
}