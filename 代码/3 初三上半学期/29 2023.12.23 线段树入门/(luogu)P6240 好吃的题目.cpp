#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m;
int h[N],w[N];
struct node{
    int l,r,t;
    int id;
}a[N],tmp1[N],tmp2[N];
int ans[N];
int dp[N][205];
void solve(int l,int r,int x,int y){  //???????
    if(x>y) return;
    if(l==r){
        for(int i=x;i<=y;i++)if(h[l]<=a[i].t)ans[a[i].id]=w[l];
        return;
    }
    int mid=(l+r)>>1;
    memset(dp[mid],0,sizeof dp[mid]);
    for(int i=h[mid];i<=200;i++) dp[mid][i]=w[mid];
    for(int i=mid-1;i>=l;i--){
        for(int j=0;j<=200;j++) dp[i][j]=dp[i+1][j];
        for(int j=200;j>=h[i];j--)dp[i][j]=max(dp[i][j],dp[i][j-h[i]]+w[i]);
    }
    memset(dp[mid+1],0,sizeof dp[mid+1]);
    for(int i=h[mid+1];i<=200;i++) dp[mid+1][i]=w[mid+1];
    for(int i=mid+2;i<=r;i++){
        for(int j=0;j<=200;j++) dp[i][j]=dp[i-1][j];
        for(int j=200;j>=h[i];j--)dp[i][j]=max(dp[i][j],dp[i][j-h[i]]+w[i]);
    }
    int cnt1=0,cnt2=0;
    for(int i=x;i<=y;i++){
        if(a[i].r<=mid) tmp1[++cnt1]=a[i];
        else if(a[i].l>mid) tmp2[++cnt2]=a[i];
        else for(int j=0;j<=min(a[i].t,200);j++)ans[a[i].id]=max(ans[a[i].id],dp[a[i].l][j]+dp[a[i].r][a[i].t-j]);
    }
    for(int i=1;i<=cnt1;i++) a[x+i-1]=tmp1[i];
    for(int i=1;i<=cnt2;i++) a[x+cnt1+i-1]=tmp2[i];
    solve(l,mid,x,x+cnt1-1);
    solve(mid+1,r,x+cnt1,x+cnt1+cnt2-1);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>h[i];
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1;i<=m;i++){
        cin>>a[i].l>>a[i].r>>a[i].t;
        a[i].id=i;
    }
    solve(1,n,1,m);
    for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}
