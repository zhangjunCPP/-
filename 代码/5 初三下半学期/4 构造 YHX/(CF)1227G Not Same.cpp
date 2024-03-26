#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1050;
struct node{int val,id;}a[N];
bool cmp(const node &x,const node &y){return x.val>y.val;}
int ans[N][N];
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].val,a[i].id=i;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        int now=a[i].id;
        for(int j=i;a[i].val;j=j%(n+1)+1)ans[j][now]=1,a[i].val--;
    }
    cout<<n+1<<"\n";
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n;j++)cout<<ans[i][j];
        cout<<"\n";
    }
    return 0;
}