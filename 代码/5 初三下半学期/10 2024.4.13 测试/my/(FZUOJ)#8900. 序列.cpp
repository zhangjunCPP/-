#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    memset(ans,0x3f,sizeof ans);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        int l=i,r=i;
        while(l>=2&&a[l-1]<=a[i])l--;
        while(r<n&&a[r+1]<=a[i])r++;
        int Min=a[i];
        for(int j=i;j>=l;j--){
            Min=min(Min,a[j]);
            int Min2=Min;
            for(int k=i;k<=r;k++){
                Min2=min(Min2,a[k]);
                ans[k-j+1]=min(ans[k-j+1],a[i]-Min2);
            }
        }
    }
    for(int i=2;i<=n;i++)cout<<ans[i]<<"\n";
}