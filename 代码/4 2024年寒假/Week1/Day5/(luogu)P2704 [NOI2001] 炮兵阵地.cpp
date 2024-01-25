#include<bits/stdc++.h>
#define int long long

using namespace std;
int a[200];
int cnt;
int flag[1005];
int sum[1005];
int dp[105][1005][1005];

int solve(int x){
    int ans=0;
    for(int i=x;i;i-=(i&-i))ans++;
    return ans;
}

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        int len=s.length();
        for(int j=0;j<len;j++)if(s[j]=='H')a[i]|=(1<<j);
    }
    for(int i=0;i<(1<<m);i++)if((!(i&(i>>1)))&&(!(i&(i>>2)))&&(!(i&(i<<1)))&&(!(i&(i<<2))))flag[++cnt]=i,sum[cnt]=__builtin_popcount(i);
    for(int i=1;i<=cnt;i++)if(!(flag[i]&a[1]))dp[1][0][i]=sum[i];
    for(int i=1;i<=cnt;i++)
        for(int j=1;j<=cnt;j++)
            if((!(flag[i]&flag[j]))&&(!(flag[j]&a[2])))dp[2][i][j]=max(dp[2][i][j],dp[1][0][i]+sum[j]);
    for(int i=3;i<=n;i++)
        for(int j=1;j<=cnt;j++) //当前
            if(!(flag[j]&a[i]))
                for(int k=1;k<=cnt;k++) //上一行
                    if(!(flag[j]&flag[k]))
                        for(int l=1;l<=cnt;l++) //上两行
                            if((!(flag[j]&flag[l]))&&(!(flag[k]&flag[l])))dp[i][k][j]=max(dp[i][k][j],dp[i-1][l][k]+sum[j]);
    int ans=0;
    for(int i=0;i<=cnt;i++)for(int j=1;j<=cnt;j++)ans=max(ans,dp[n][i][j]);
    cout<<ans;
    return 0;
}