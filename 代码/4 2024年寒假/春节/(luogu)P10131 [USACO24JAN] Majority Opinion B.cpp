#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;

int a[N];
vector<int>ans;
void solve(){
    ans.clear();
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(n==2&&a[1]==a[2]){
        cout<<a[1]<<endl;
        return;
    }
    for(int i=3;i<=n;i++){
        int a1=a[i-2],a2=a[i-1],a3=a[i];
        if(a1==a2||a1==a3) ans.push_back(a1);
        if(a2==a3) ans.push_back(a2);
    }
    if(ans.empty()){
        cout<<"-1\n";
        return;
    }
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)if(ans[i]!=ans[i-1])cout<<ans[i]<<" ";
    cout<<"\n";
}
signed main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}