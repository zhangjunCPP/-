#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3005;
int t[N];
vector<int> a[N];
int sum[N];
int n,k;
int dp[N],tmp[N][30];
int ans=-1;
void solve(int l,int r,int dep){
    if(l==r){
        int x=0;
        for(int i=0;i<=min(k,t[l]);i++) {
            ans=max(ans,dp[k-i]+x);
            x+=a[l][i];
        }
        return ;
    }
    int mid=(l+r)>>1;
    for(int i=0;i<=k;i++) tmp[i][dep]=dp[i];
    for(int i=mid+1;i<=r;i++) {
        for(int j=k;j>=t[i];j--) {
            dp[j]=max(dp[j],dp[j-t[i]]+sum[i]);
        }
    }
    solve(l,mid,dep+1);
    for(int i=0;i<=k;i++) dp[i]=tmp[i][dep];
    for(int i=l;i<=mid;i++) {
        for(int j=k;j>=t[i];j--) {
            dp[j]=max(dp[j],dp[j-t[i]]+sum[i]);
        }
    }
    solve(mid+1,r,dep+1);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) {
        cin>>t[i];
        for(int j=1;j<=t[i];j++){
            int x;
            cin>>x;
            a[i].push_back(x); 
            sum[i]+=x;
        }
    }
    solve(1,n,1);
    cout<<ans;
}
