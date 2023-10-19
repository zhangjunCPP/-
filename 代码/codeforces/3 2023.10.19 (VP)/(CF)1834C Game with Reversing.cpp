#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
void solve() {
    int n;
    cin>>n;
    string s1,s2;
    cin>>s1>>s2;
    int ans1=0,ans2=0;
    int siz=s1.size();
    for(int i=0;i<siz;i++) {
        if(s1[i]!=s2[i]) ans1++;
        if(s1[i]!=s2[siz-i-1]) ans2++;
    }
    if(ans1<=1) {
        cout<<ans1<<"\n";
        return;
    }
    if(ans2<=1) {
        cout<<"2\n";
        return;
    }
    int ans=0x3f3f3f3f;
    if(ans1&1) ans=min(ans,ans1*2-1);
    else ans=min(ans,ans1*2);
    if(ans2&1) ans=min(ans,ans2*2);
    else ans=min(ans,ans2*2-1);
    cout<<ans<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}