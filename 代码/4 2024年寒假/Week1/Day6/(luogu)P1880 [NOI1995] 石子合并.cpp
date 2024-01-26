#include<bits/stdc++.h>
using namespace std;
const int N=405;
int dp1[N][N],dp2[N][N];
int sum[N];
int a[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];a[i+n]=a[i];}
    n*=2;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    memset(dp1,0x3f,sizeof dp1);
    for(int i=1;i<=n;i++) dp1[i][i]=0;
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<=j-1;k++){
                dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
                dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    n/=2;
    int ans1=dp1[1][n],ans2=dp2[1][n];
    for(int i=2;i<=n;i++) ans1=min(ans1,dp1[i][i+n-1]),ans2=max(ans2,dp2[i][i+n-1]);
    cout<<ans1<<"\n"<<ans2;
}