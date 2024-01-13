#include<bits/stdc++.h>
using namespace std;
const int N=35000+10;
int dp[N][105];
int a[N];
int pre[N],nex[N];
int tmp[N];
int L=1,R=0;
int ans=0;
int calc(int l,int r){
    while(L>l){
        --L;
        if(nex[L]<=R)ans+=nex[L]-L;
    }
    while(L<l){
        if(nex[L]<=R)ans-=nex[L]-L;
        L++;
    }
    while(R<r){
        ++R;
        if(pre[R]>=L)ans+=R-pre[R];
    }
    while(R>r){
        if(pre[R]>=L)ans-=R-pre[R];
        R--;
    }
    return ans;
}
void solve(int now,int l,int r,int x,int y){
    if(l>r||x>y) return;
    int mid=(l+r)>>1;
    //dp[mid][now]=dp[k][now-1]+calc(k+1,mid)
    int pos,Min=0x3f3f3f3f;
    for(int i=x;i<=min(y,mid);i++){
        int tmp=dp[i][now-1]+calc(i+1,mid);
        if(tmp<Min) Min=tmp,pos=i;
    }
    dp[mid][now]=Min;
    solve(now,l,mid-1,x,pos);
    solve(now,mid+1,r,pos,y);
}
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)dp[i][0]=0x3f3f3f3f;
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=1;i<=n;i++){
        pre[i]=tmp[a[i]];
        tmp[a[i]]=i;
    }
    for(int i=1;i<=n;i++)tmp[a[i]]=n+1;
    for(int i=n;i>=1;i--){
        nex[i]=tmp[a[i]];
        tmp[a[i]]=i;
    }
    for(int i=1;i<=k;i++)solve(i,1,n,0,n);
    cout<<dp[n][k];
}