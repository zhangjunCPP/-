#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;

signed main(){
    int n;
    cin>>n;
    int cnt=0;
    int ans=0;
    int Min=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        if(a<b)swap(a,b);
        else cnt++;
        ans+=a;
        Min=min(Min,a-b);
    }
    if(cnt&1)ans-=Min;
    cout<<ans;
}