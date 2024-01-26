#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
int c[N][2];
int dp[N][N];
signed main(){
    int n,m;
    string s;
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++) {
        char ch;
        cin>>ch;
        cin>>c[ch-'a'][0]>>c[ch-'a'][1];
    }
    memset(dp,0x3f,sizeof dp);
    for(int i=0;i<m;i++) dp[i][i]=0;
    for(int len=2;len<=m;len++){
        for(int i=0;i+len-1<m;i++) {
            int j=i+len-1;
            dp[i][j]=min(dp[i][j],dp[i+1][j]+min(c[s[i]-'a'][0],c[s[i]-'a'][1]));
            dp[i][j]=min(dp[i][j],dp[i][j-1]+min(c[s[j]-'a'][0],c[s[j]-'a'][1]));
            if(s[i]==s[j]){
                if(len==2) dp[i][j]=0;
                else dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
            }
        }
    }
    cout<<dp[0][m-1];
}