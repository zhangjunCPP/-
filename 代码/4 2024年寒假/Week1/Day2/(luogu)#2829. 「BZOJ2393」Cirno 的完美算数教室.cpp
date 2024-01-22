#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int a[N],cnt;
int l,r;
void init(int now){
    if(now>r) return;
    a[++cnt]=now;
    init(now*10+2);
    init(now*10+9);
}
int gcd(int x,int y){
    while(y^=x^=y^=x%=y);
    return x;
}
int ans;
int lcm(int x,int y){return x/gcd(x,y)*y;}
void dfs(int k,int sum,int val){
    if(val!=1){
        int tmp=r/val-(l-1)/val;
        ans+=sum&1?tmp:-tmp;
    }
    for(int i=k+1;i<=cnt;i++){
        if(lcm(val,a[i])<=r)dfs(i,sum+1,lcm(val,a[i]));
    }
}
bool cmp(int x,int y){return x>y;}
signed main(){
    cin>>l>>r;
    init(2);init(9);
    sort(a+1,a+cnt+1,cmp);
    dfs(0,0,1);
    cout<<ans;
}