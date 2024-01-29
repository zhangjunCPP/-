/*
 * 感觉很像前几天的一道题
 * 直接枚举最后的GCD，把是GCD倍数的都保留，其它的都删去。
 *
 * 发现m很大，因此用map
 *
 * 秒了。
 *
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
map<int,int> mp;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=2;j*j<=a[i];j++){
            if(a[i]%j==0){
                mp[j]+=a[i];
                if(j*j!=a[i]) mp[a[i]/j]+=a[i];
            }
        }
        if(a[i]!=1) mp[a[i]]+=a[i];
    }
    int ans=0;
    for(auto i:mp) ans=max(ans,i.second);
    cout<<ans;
}