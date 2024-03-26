#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
bool flag[N*10];
int prime[N*10],cnt;
void init(){
    for(int i=2;i<N*10;i++){
        if(!flag[i])prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<N*10;j++){
            flag[i*prime[j]]=true;
            if(!i%prime[j])break;
        }
    }
}
int gcd(int x,int y){
    while(y^=x^=y^=x%=y);
    return x;
}
int lcm(int x,int y){
    if(!x||!y)return x+y;
    return x/gcd(x,y)*y;
}
int a[N][N];
signed main(){
    int n;
    cin>>n;
    if(n==2){
        puts("4 7\n23 10");
        return 0;
    }
    init();
    for(int i=1;i<=n;i++)for(int j=1+!(i&1);j<=n;j+=2)a[i][j]=prime[(i+j)/2]*prime[n+(j-i)/2+1];
    for(int i=1;i<=n;i++)for(int j=1+(i&1);j<=n;j+=2)a[i][j]=lcm(lcm(lcm(a[i][j-1],a[i][j+1]),a[i-1][j]),a[i+1][j])+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";
        cout<<"\n";
    }
}