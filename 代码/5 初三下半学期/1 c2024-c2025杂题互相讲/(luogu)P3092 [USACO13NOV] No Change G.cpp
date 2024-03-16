#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int k,n;
int dp[N];
int a[N];
int sum[N];
int calc(int x,int y){
    int l=x,r=n;
    int ans=x;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sum[mid]-sum[x-1]<=y)ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
int main(){
    cin>>k>>n;
    for(int i=1;i<=k;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        cin>>sum[i];
        sum[i]+=sum[i-1];
    }
    for(int i=0;i<(1<<k);i++){
        for(int j=1;j<=k;j++){
            if(i&(1<<(j-1))){
                int pre=i^(1<<(j-1));
                dp[i]=max(dp[i],calc(dp[pre]+1,a[j]));
            }
        }
    }
    int ans=-1;
    for(int i=0;i<(1<<k);i++){
        if(dp[i]==n){
            int tmp=0;
            for(int j=1;j<=k;j++)if(!(i&(1<<(j-1))))tmp+=a[j];
            ans=max(ans,tmp);
        }
    }
    cout<<ans;
}