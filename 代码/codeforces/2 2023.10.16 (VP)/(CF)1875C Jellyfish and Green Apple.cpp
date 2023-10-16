#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;

int gcd(int x,int y){
    while(y) x%=y,x^=y^=x^=y;
    return x;
}
void solve(){
    int n,m;
    cin>>n>>m;
    n%=m;
    int GCD=gcd(n,m);
    int tmp1=n/GCD,tmp2=m/GCD;
    int tmp=log2(tmp2);
    if(tmp2!=pow(2,tmp)) {
        cout<<"-1"<<endl;
        return;
    }
    cout<<__builtin_popcount(tmp1)*m-n<<endl;

}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}