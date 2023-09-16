#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=50005;
int a,n,b,p;
int prime[N],phi[N],cnt;
bool flag[N];
void init(){
    phi[1]=1;
    for(int i=2;i<N;i++){
        if(!flag[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<N;j++){
            flag[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
int BSGS(int a,int b,int mod){
    unordered_map<int,int> mp;
    if(b==1)return 0;
    int t=ceil(sqrt(mod));
    int tmp=1;
    for(int i=0;i<t;i++){
        mp[b*tmp%mod]=i;
        tmp=tmp*a%mod;
    }
    int now=1;
    for(int i=1;i<=t;i++){
        now=tmp*now%mod;
        if(mp.count(now))return i*t-mp[now];
    }
    return -1;
}
int getphi(int x){
    int ans=x;
    for(int i=1;i<=cnt&&prime[i]*prime[i]<=x;i++)
        if(x%prime[i]==0){
            ans=ans/prime[i]*(prime[i]-1);
            while(x%prime[i]==0) x/=prime[i];
        }
    if(x>1) ans=ans/x*(x-1);
    return ans;
}
struct node{
    int x;
    bool flag;
};
node qpow(int x,int y,int mod){
    int ans=1;
    bool f=false;
    if(x>=mod)f=true,x%=mod;
    while(y){
        if(y&1){
            ans=ans*x;
            if(ans>=mod) f=true,ans%=mod;
        }
        y>>=1;
        x=x*x;
        if(x>=mod)f=true,x%=mod;
    }
    return (node){ans,f};
}
int Phi[N];
node calc(int a,int n,int id){
    int m=Phi[id];
    int tmp=Phi[id+1];
    if(m==1)return {0,true};
    if(n==0)return {1,false};
    node now=calc(a,n-1,id+1);
    if(now.flag)now.x+=tmp;
    return qpow(a,now.x,m);
}
void solve(){
    cin>>a>>n>>b>>p;
    if(b==1||p==1){
        puts("0");
        return;
    }
    b%=p;
    if(n==1){
        cout<<BSGS(a,b,p)<<"\n";
        return;
    }
    Phi[1]=p;
    int tot=1;
    while(1){
        tot++;
        if(Phi[tot-1]>N-5)Phi[tot]=getphi(Phi[tot-1]);
        else Phi[tot]=phi[Phi[tot-1]];
        if(Phi[tot]==1) break;
    }
    if(n==2){
        for(int i=1;i<=tot;i++){
            if(calc(a,i,1).x==b){
                cout<<i<<"\n";
                return;
            }
        }
        puts("-1");
        return;
    }
    if(n==3){
        if(a==1){
            puts("-1");
            return;
        }
        if(b==a%p){
            puts("1");
            return;
        }
        if(a==2){
            if(b==4%p) puts("2");
            else if(b==65536%p) puts("3");
            else if(b==calc(a,100,1).x%p) puts("4");
            else puts("-1");
            return;
        }
        if(b==calc(a,a,1).x)puts("2");
        else if(b==calc(a,100,1).x)puts("3");
        else puts("-1");
    }
}
signed main(){
    init();
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}