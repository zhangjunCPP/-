#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,d,k;

struct node{int x,s;}a[N];

int dp[N];
int q[N];
bool check(int mid){
    memset(dp,128,sizeof dp);
    dp[0]=0;

    int Min=max(d-mid,1ll),Max=d+mid;
    int ans=0;
    int l=1,r=0;
    int now=0;
    for(int i=1;i<=n;i++){
        //insert(now)
        while(a[i].x-a[now].x>=Min){
            while(l<=r&&dp[q[r]]<=dp[now])r--;
            q[++r]=now++;
        }
        while(l<=r&&a[i].x-a[q[l]].x>Max)l++;
        if(l<=r)dp[i]=dp[q[l]]+a[i].s;
        ans=max(ans,dp[i]);
    }
    return ans>=k;
}
signed main(){
    cin>>n>>d>>k;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].s;
    int l=0,r=1e9+10;
    int ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}