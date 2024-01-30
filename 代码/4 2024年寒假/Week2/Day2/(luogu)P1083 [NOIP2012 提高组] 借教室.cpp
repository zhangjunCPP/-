#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m;
int rest[N],d[N],l[N],r[N];
int diff[N],need[N];
bool check(int x) {
    memset(diff,0,sizeof(diff));
    for(int i=1;i<=x;i++) {
        diff[l[i]]+=d[i];
        diff[r[i]+1]-=d[i];
    }
    for(int i=1;i<=n;i++) {
        need[i]=need[i-1]+diff[i];
        if(need[i]>rest[i])return false;
    }
    return true;
}
signed main() {
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>rest[i];
    for(int i=1;i<=m;i++)cin>>d[i]>>l[i]>>r[i];
    int le=0,ri=m+10;
    if(check(m)) {
        puts("0");
        return 0;
    }
    while(le<ri) {
        int mid=(le+ri)>>1;
        if(check(mid))le=mid+1;
        else ri=mid;
    }
    cout<<"-1\n"<<le;
    return 0;
}