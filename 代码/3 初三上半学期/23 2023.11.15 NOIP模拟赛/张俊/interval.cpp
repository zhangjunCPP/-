#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
struct node{
    int l,r,id;
}a[N];
bool cmp(const node &x,const node &y) {
    if(x.r==y.r) return x.l<y.l;
    return x.r<y.r;
}
int dp[N];
int dp2[N];
int dp3[N];
int main(){
    freopen("interval.in","r",stdin);
    freopen("interval.out","w",stdout);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i].l>>a[i].r;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    // for(int i=1;i<=n;i++) {
    //     cout<<a[i].l<<" "<<a[i].r<<"\n";
    // }
    for(int i=1;i<=n;i++) {
        // for(int j=1;j<i;j++) dp[i]=max(dp[i],dp[j]);
        for(int j=1;j<i;j++) {
            if(a[j].r<a[i].l){
                dp[i]=1;
                dp2[i]=j;
                for(int k=1;k<j;k++){
                    if(dp[k]+1>dp[i]){
                        dp[i]=dp[k]+1;
                        dp2[i]=dp2[k];
                    }
                }
            }
        }    
    }
    // for(int i=1;i<=n;i++) cout<<dp[i]<<" ";
    // cout<<"\n";
    int ans=0;
    for(int i=1;i<=n;i++) {
        dp3[i]=dp[i];
        for(int j=1;j<dp2[i];j++) dp3[i]+=dp3[j];
    }
    for(int i=1;i<=n;i++) ans=max(ans,dp3[i]);
    cout<<ans;


}