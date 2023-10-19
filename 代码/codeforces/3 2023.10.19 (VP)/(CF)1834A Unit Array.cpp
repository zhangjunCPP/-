#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
void solve(){
    int n;
    cin>>n;
    int sum1=0,sum2=0;
    for(int i=1;i<=n;i++) {
        int x;
        cin>>x;
        if(x==1) sum1++;
        else sum2++;
    }
    if(sum1>=sum2){
        if(sum2&1) cout<<"1\n";
        else cout<<"0\n";
    }
    else{
        int ans=0;
        while(sum1<sum2) sum1++,sum2--,ans++;
        if(sum2&1) cout<<ans+1<<"\n";
        else cout<<ans<<"\n";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}