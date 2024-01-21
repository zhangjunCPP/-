#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int exgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    int gcd=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return gcd;
}
int mul(int x,int y,int mod){
    int ans=0;
    while(y){
        if(y&1) ans=(ans+x%mod)%mod;
        y>>=1;
        x=(x+x)%mod;
    }
    return ans%mod;
}
int m[N],a[N];
int n;
int excrt(){
    int ans=a[1],M=m[1];
    for(int i=2;i<=n;i++){
        int A=M,B=m[i],C=(a[i]-ans%B+B)%B,x,y;
        int gcd=exgcd(A,B,x,y);
        int lcm=B/gcd*M;
        x=mul(x,C/gcd,B);
        ans=(ans+x*M)%lcm;
        M=lcm;
    }
    return (ans+M)%M;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>m[i]>>a[i];
    cout<<excrt();
}