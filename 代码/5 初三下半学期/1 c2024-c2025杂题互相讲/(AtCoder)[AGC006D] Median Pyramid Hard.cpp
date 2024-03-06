#include <bits/stdc++.h>

using namespace std;
const int N=2e5+10;
int n;
int a[N];
bool check(int mid){
    for(int i=0;i<n-1;i++){
        if((a[n+i]>mid&&a[n+i+1]>mid)||(a[n-i]>mid&&a[n-i-1]>mid))return true;
        if((a[n+i]<=mid&&a[n+i+1]<=mid)||(a[n-i]<=mid&&a[n-i-1]<=mid))return false;
    }
    return a[1]>mid;
}
int main(){
    cin>>n;
    for(int i=1;i<=n*2-1;i++)cin>>a[i];
    int l=1,r=2*n-1;
    int ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))l=mid+1;
        else ans=mid,r=mid-1;
    }
    cout<<ans;
}