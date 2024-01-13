#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e18;
const int N=1e5+10;
int a[N];
int dp[N][30];

int cnt[N],sum;
int L=1,R=0;
int calc(int x,int y){
    while(L>x) sum+=cnt[a[--L]]++;
    while(R<y) sum+=cnt[a[++R]]++;
    while(L<x) sum-=--cnt[a[L++]];
    while(R>y) sum-=--cnt[a[R--]];
    return sum;
}
void solve(int now,int l,int r,int x,int y){
    if(l>r) return;
    int mid=(l+r)>>1;
    int Min=INF,id;
    for(int i=max(1ll,x);i<=min(mid,y);i++) {
        int tmp=dp[i-1][now-1]+calc(i,mid);
        if(tmp<Min) Min=tmp,id=i;
    }
    dp[mid][now]=Min;
    solve(now,l,mid-1,x,id);
    solve(now,mid+1,r,id,y);
}
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    dp[0][0]=0;
    for(int i=1;i<=n;i++) dp[i][0]=INF;
    for(int i=1;i<=k;i++) solve(i,1,n,1,n);
    cout<<dp[n][k];
}