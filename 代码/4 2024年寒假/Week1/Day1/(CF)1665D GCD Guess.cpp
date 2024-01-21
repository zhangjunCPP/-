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
int a[N];
const int num=1070845776;
int p[10]={7,9,11,13,16,17,19,23};
int crt(){
    int M=num;
    int ans=0;
    for(int i=0;i<8;i++){
        int mi=M/p[i];
        int x,y;
        exgcd(mi,p[i],x,y);
        x=(x%p[i]+p[i])%p[i];
        ans=(ans+a[i]*mi%M*x%M)%M;
    }
    return ans;
}
void solve(){
    for(int i=0;i<=10;i++)a[i]=0;
    for(int i=1;i<=22;i++){
        cout<<"? "<<i<<" "<<num+i<<endl;
        int tmp;
        cin>>tmp;
        for(int j=0;j<8;j++)if(tmp%p[j]==0)a[j]=(p[j]-i%p[j])%p[j];
    }
    cout<<"! "<<crt()<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)solve();
}