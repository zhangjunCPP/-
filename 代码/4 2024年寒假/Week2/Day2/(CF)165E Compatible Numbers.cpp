#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
int a[N];
int dp[N];
signed main(){
    int n;
    cin>>n;
    memset(dp,-1,sizeof dp);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        dp[a[i]]=a[i];
    }
    for(int i=0;i<=21;i++)for(int j=0;j<(1<<22);j++)if( (j&(1<<i)) &&dp[j^(1<<i)]!=-1)dp[j]=dp[j^(1<<i)];
    for(int i=1;i<=n;i++){
        int tmp=((1<<22)-1)^a[i];
        cout<<dp[tmp]<<" ";
    }
    return 0;
}