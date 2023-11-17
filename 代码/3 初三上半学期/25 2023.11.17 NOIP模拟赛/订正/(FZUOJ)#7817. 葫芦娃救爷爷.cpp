#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
double p[N];
double dp[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i],p[i]+=p[i-1];
    dp[n+1]=0;
    for(int i=n;i>=1;i--) {
        for(int j=i;j<=n;j++){
            double tmp=p[j]-p[i-1];
            dp[i]=max(dp[i],(tmp+(1-tmp)*dp[j+1])*(n-j)/(n-i+1));
        }
    }
    cout<<dp[1]<<endl;
    return 0;
}
