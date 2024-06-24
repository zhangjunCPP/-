#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n;
int a[N],b[N];
int p[N],q[N];
int calc(int f[]){
    sort(f+1,f+n+1);
    int sum=0;
    for(int i=1;i<n;i++)sum+=i*(n-i)*(f[i+1]-f[i]);
    return sum;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++){
        p[i]=a[i]+b[i];
        q[i]=a[i]-b[i];
        a[i]*=2,b[i]*=2;
    }
    cout<<calc(a)+calc(b)-calc(p)-calc(q);
}