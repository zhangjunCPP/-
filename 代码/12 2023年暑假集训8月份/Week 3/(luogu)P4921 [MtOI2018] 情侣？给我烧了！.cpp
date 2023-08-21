#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=2e3+10;
int C[N][N];
int g[N];
int pw[N],jc[N];

int a[N];
int solve(int n,int k){
    return C[n][k]%mod*C[n][k]%mod*jc[k]%mod*pw[k]%mod*a[n-k]%mod;
}
void init(){
    pw[0]=jc[0]=1;
    for(int i=1;i<N;i++) {
        jc[i]=jc[i-1]*i%mod;
        pw[i]=pw[i-1]*2%mod;
    }
    for(int i=0;i<N;i++) C[i][0]=C[i][i]=1;
    for(int i=1;i<N;i++)for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;

    a[0]=1;
    for(int i=1;i<N;i++){
        a[i]=jc[2*i]%mod;
        for(int j=1;j<=i;j++)a[i]=(a[i]-solve(i,j)+mod)%mod;
    }
}
signed main(){
    init();
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=0;i<=n;i++)cout<<solve(n,i)<<"\n";
    }
}