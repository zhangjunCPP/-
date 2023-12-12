#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;
string w[N];
string tmp[N];
bool cmp1(const char &x,const char &y) {return x<y;}
bool cmp2(const char &x,const char &y) {return x>y;}
int main(){
    freopen("dict.in","r",stdin);
    freopen("dict.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) tmp[j]=w[j];
        for(int j=1;j<=n;j++) {
            string tmpp=tmp[j];
            if(tmp[j]>tmp[i]) continue;
            if(j==i) sort(tmpp.begin(),tmpp.end(),cmp1);
            else sort(tmpp.begin(),tmpp.end(),cmp2);
            tmp[j]=tmpp;
        }
        bool flag=true;
        for(int j=1;j<=n;j++) {
            if(j==i) continue;
            if(tmp[i]>=tmp[j]) {flag=false;break;}
        }
        if(flag) cout<<1;
        else cout<<0;
    }
}