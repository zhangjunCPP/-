#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,k;
int a[N];
int dp[N];
int tmp[N];
int sum[N];
bool check(int mid){
    for(int i=0;i<=mid;i++)tmp[i]=a[i];
    sort(tmp,tmp+mid);
    sum[0]=tmp[0];
    for(int i=1;i<mid;i++)sum[i]=sum[i-1]+tmp[i];
    int l=1;
    for(int r=1;r<mid;r++){
        while(sum[r]-sum[l-1]>l*k+tmp[l]*(r-l+1))l++;
        if(sum[r]-sum[l-1]-(l-1)*k<=dp[r-l+1])return true;
    }
    return false;
}
void solve(){
    cin>>n>>k;
    for(int i=0;i<=n;i++)cin>>a[i];
    dp[1]=k;
    for(int i=2;i<=n+1;++i)dp[i]=(long double)i*dp[i-1]/(i-1)+k;
    int l=0,r=n+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<l-check(l)<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)solve();
}