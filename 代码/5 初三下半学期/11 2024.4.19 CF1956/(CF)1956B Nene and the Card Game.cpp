#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int sum[N];
void solve(){
    memset(sum,0,sizeof sum);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sum[x]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(sum[i]==2)ans++;
    cout<<ans<<"\n";
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
}