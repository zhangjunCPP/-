#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int cf[N];
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cf[i]=a[i]-a[i-1];
    int sum1=0,sum2=0;
    for(int i=2;i<=n;i++) {if(cf[i]>0)sum1+=cf[i]; else sum2-=cf[i];}
    cout<<max(sum1,sum2)<<"\n";
    cout<<llabs(sum1-sum2)+1;
}