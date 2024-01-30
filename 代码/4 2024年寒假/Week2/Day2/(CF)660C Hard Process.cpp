#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(k==0){
        int ans=0;
        int tmp=0;
        for(int i=1;i<=n;i++){
            tmp+=a[i];
            ans=max(ans,tmp);
            if(a[i]==0) tmp=0;
        }
        cout<<ans<<"\n";
        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        return 0;
    }
    int ans=0,ans1=0,ans2=0;
    int l=1,r=1;
    int cnt=!a[1];
    while(l<=r&&r<=n){
        if(cnt<=k) {
            if(r-l+1>ans){
                ans=r-l+1;
                ans1=l,ans2=r;
            }
            r++;
            cnt+=!a[r];
        }
        else cnt-=!a[l],l++;
    }
    cout<<ans<<"\n";
    for(int i=ans1;i<=ans2;i++) a[i]=1;
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}