#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int b[N];
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    k--;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)cin>>b[i];
    int id1=1,id2=1;
    for(int i=2;i<=n;i++) if(a[id1]>a[i]) id1=i;
    for(int i=2;i<=m;i++) if(b[id2]<b[i]) id2=i;
    if(b[id2]>a[id1])swap(a[id1],b[id2]);
    if(k&1) {
        id1=1,id2=1;
        for(int i=2;i<=n;i++) if(a[id1]<a[i]) id1=i;
        for(int i=2;i<=m;i++) if(b[id2]>b[i]) id2=i;
        swap(a[id1],b[id2]);
    }
    int sum=0;
    for(int i=1;i<=n;i++) sum+=a[i];
    cout<<sum<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){solve();}
    return 0;
}