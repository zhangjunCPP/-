#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int dp[N][40];
int sum[N][40];
signed main(){
    int n,c;
    cin>>n>>c;
    for(int i=1;i<=c;i++) {
        int e,f,l;
        cin>>e>>f>>l;
        int fear=0,like=0;
        for(int j=1;j<=f;j++) {
            int x;
            cin>>x;
            x=(x-e+n)%n;
            fear|=1<<x;
        }
        for(int j=1;j<=l;j++) {
            int x;
            cin>>x;
            x=(x-e+n)%n;
            like|=(1<<x);
        }
        for(int j=0;j<32;j++) if((~j&like)||(j&fear)) sum[e][j]++;
    }
    int ans=-0x3f3f3f3f;
    for(int i=0;i<32;i++){
        memset(dp,128,sizeof dp);
        dp[0][i]=0;
        for(int j=1;j<=n;j++){
            for(int s=0;s<32;s++) {
                dp[j][s]=max(dp[j-1][(s&15)<<1],dp[j-1][((s&15)<<1)|1])+sum[j][s];
            }
        }
        ans=max(ans,dp[n][i]);
    }
    cout<<ans;
}