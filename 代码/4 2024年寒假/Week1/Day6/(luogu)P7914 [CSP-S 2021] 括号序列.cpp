#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=505;
int dp[N][N][5];
//0:**** 1:(****) 2:(*)**(**)** 3:(*)**(**) 4:**(*)(*)
signed main(){
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    for(int i=1;i<n;i++) dp[i][i-1][0]=1;
    for(int i=0;i<n;i++) dp[i][i][0]=(s[i]=='*'||s[i]=='?');
    for(int len=2;len<=n;len++){
        for(int i=0;i+len-1<n;i++){
            int j=i+len-1;
            if(len<=k&&dp[i][j-1][0]&&(s[j]=='*'||s[j]=='?')) dp[i][j][0]=1;
            if((s[i]=='('||s[i]=='?')&&(s[j]==')'||s[j]=='?')) dp[i][j][1]=(dp[i+1][j-1][0]+dp[i+1][j-1][2]+dp[i+1][j-1][3]+dp[i+1][j-1][4])%mod;
            for(int l=i;l<j;l++){
                dp[i][j][2]=(dp[i][j][2]+dp[i][l][3]*dp[l+1][j][0])%mod;
                dp[i][j][3]=(dp[i][j][3]+(dp[i][l][2]+dp[i][l][3])*dp[l+1][j][1]%mod)%mod;
                dp[i][j][4]=(dp[i][j][4]+dp[i][l][0]*dp[l+1][j][3])%mod;
            }
            dp[i][j][3]=(dp[i][j][3]+dp[i][j][1])%mod;
        }
    }
    cout<<dp[0][n-1][3];
}