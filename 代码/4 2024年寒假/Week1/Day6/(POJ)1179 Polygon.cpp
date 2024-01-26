#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=105;
int dp1[N][N];//max
int dp2[N][N];//min
int opt[N],a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch>>a[i];
        if(ch=='t') opt[i]=1;
        else opt[i]=0;
        opt[i+n]=opt[i];
        a[i+n]=a[i];
    }
    n*=2;
    memset(dp1,128,sizeof dp1);
    memset(dp2,63,sizeof dp2);
    for(int i=1;i<=n;i++) dp1[i][i]=dp2[i][i]=a[i];
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                if(opt[k+1]){
                    dp1[i][j]=max(dp1[i][j],dp1[i][k]+dp1[k+1][j]);
                    dp2[i][j]=min(dp2[i][j],dp2[i][k]+dp2[k+1][j]);
                }
                else {
                    dp1[i][j]=max(dp1[i][j],dp1[i][k]*dp1[k+1][j]);
                    dp1[i][j]=max(dp1[i][j],dp2[i][k]*dp2[k+1][j]);

                    dp2[i][j]=min(dp2[i][j],dp1[i][k]*dp2[k+1][j]);
                    dp2[i][j]=min(dp2[i][j],dp2[i][k]*dp1[k+1][j]);
                    dp2[i][j]=min(dp2[i][j],dp2[i][k]*dp2[k+1][j]);
                }
            }
        }
    }
    n/=2;
    int ans=dp1[1][n];
    for(int i=2;i<=n;i++) ans=max(ans,dp1[i][i+n-1]);
    cout<<ans<<"\n";
    for(int i=1;i<=n;i++) if(dp1[i][i+n-1]==ans) cout<<i<<" ";
}