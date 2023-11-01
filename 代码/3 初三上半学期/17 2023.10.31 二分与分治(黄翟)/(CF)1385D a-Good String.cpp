#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int solve(int l,int r,int c){
    if(l==r){
        if(s[l]-'a'!=c) return 1;
        else return 0;
    }
    int mid=(l+r)>>1;
    int sum1=0,sum2=0;
    for(int i=l;i<=mid;i++) sum1+=(s[i]-'a'!=c);
    for(int i=mid+1;i<=r;i++) sum2+=(s[i]-'a'!=c);
    sum1+=solve(mid+1,r,c+1);
    sum2+=solve(l,mid,c+1);
    return min(sum1,sum2);
}
signed main(){
    int T;
    cin>>T;
    while(T--) {
        int n;
        cin>>n>>s;
        cout<<solve(0,n-1,0)<<"\n";
    }
}