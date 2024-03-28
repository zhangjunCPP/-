#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<18),mod=998244353;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans;
}
const int inv2=qpow(2,mod-2);
int a[N],b[N];
int c[3][2][2]={
        {{1,0},{1,1}},
        {{1,1},{0,1}},
        {{1,1},{1,mod-1}}
};
int ic[3][2][2]={
        {{1,0},{mod-1,1}},
        {{1,mod-1},{0,1}},
        {{inv2,inv2},{inv2,mod-inv2}}
};
int n;
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
int tmp_a[N],tmp_b[N];
void solve(int t){
    memcpy(tmp_a,a,sizeof tmp_a);
    memcpy(tmp_b,b,sizeof tmp_b);
    FWT(tmp_a,c[t]);FWT(tmp_b,c[t]);
    for(int i=0;i<n;i++)tmp_a[i]=tmp_a[i]*tmp_b[i]%mod;
    FWT(tmp_a,ic[t]);
    for(int i=0;i<n;i++)cout<<tmp_a[i]<<" ";
    cout<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n;
    n=(1<<n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    solve(0);
    solve(1);
    solve(2);
}