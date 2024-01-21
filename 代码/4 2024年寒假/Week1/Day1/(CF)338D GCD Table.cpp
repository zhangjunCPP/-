#include<bits/stdc++.h>
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
        if(y&1) ans=(ans+x)%mod;
        y>>=1;
        x=(x+x)%mod;
    }
    return ans%mod;
}
int lcm(int x,int y){
    int tmp1,tmp2;
    int gcd=exgcd(x,y,tmp1,tmp2);
    return x/gcd*y;
}
int a[N],p[N];

int k;
int excrt(){
    int ans=a[1],M=p[1];
    for(int i=2;i<=k;i++){
        int A=M,B=p[i],C=((a[i]-ans)%B+B)%B;
        int x,y;
        int gcd=exgcd(A,B,x,y);
        if(C%gcd) return -1;
        x=mul(x,C/gcd,B);
        int Lcm=M/gcd*p[i];
        ans=(ans+x*M)%Lcm;
        M=Lcm;
    }
    if(ans%M==0) return M;
    return (ans%M+M)%M;
}
int gcd(int x,int y){
    int tmp1,tmp2;
    return exgcd(x,y,tmp1,tmp2);
}
signed main(){
    int n,m;
    cin>>n>>m>>k;
    int x=1;
    for(int i=1;i<=k;i++){
        cin>>p[i];
        x=lcm(x,p[i]);
        if(x>n){puts("NO");return 0;}
        a[i]=((p[i]-i+1)%p[i]+p[i])%p[i];
    }
    int y=excrt();
    if(y==0){puts("NO");return 0;}
    if(y+k-1>m){puts("NO");return 0;}
    for(int i=1;i<=k;i++){
        if(__gcd(x,y+i-1)!=p[i]){puts("NO");return 0;}
    }
    puts("YES");
}