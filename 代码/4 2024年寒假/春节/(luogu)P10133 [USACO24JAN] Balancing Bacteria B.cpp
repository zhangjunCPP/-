#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N];
int s[N],s2[N];
signed main(){
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=a[i]-a[i-1];
        s2[i]=s[i]-s[i-1];
        ans+=llabs(s2[i]);
    }
    cout<<ans;
}
