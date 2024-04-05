#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e6+10,mod=1e9+9;
int n;
int a[22][N],b[22][N];
int c[2][2]={
        {1,0},
        {1,1}
};
int ic[2][2]={
        {1,0},
        {mod-1,1}
};
void FWT(int *A,int C[2][2]){
    for(int len=1;len<n;len*=2){
        for(int st=0;st<n;st+=len*2){
            for(int i=st;i<st+len;i++){
                int tmp=A[i];
                A[i]=(C[0][0]*A[i]+C[0][1]*A[i+len])%mod;
                A[i+len]=(C[1][0]*tmp+C[1][1]*A[i+len])%mod;
            }
        }
    }
}
int h[22][N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n;
    int _n=n;
    n=(1<<n);
    for(int i=0;i<n;i++)cin>>a[__builtin_popcount(i)][i];
    for(int i=0;i<n;i++)cin>>b[__builtin_popcount(i)][i];
    for(int i=0;i<=_n;i++){
        FWT(a[i],c);
        FWT(b[i],c);
    }
    for(int i=0;i<=_n;i++)for(int j=0;j<=i;j++)for(int k=0;k<n;k++)h[i][k]=(h[i][k]+a[j][k]*b[i-j][k]%mod)%mod;
    for(int i=0;i<=_n;i++)FWT(h[i],ic);
    for(int i=0;i<n;i++)cout<<h[__builtin_popcount(i)][i]<<" ";
}