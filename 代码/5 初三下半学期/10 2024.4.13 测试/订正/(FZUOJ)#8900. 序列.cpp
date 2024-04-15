#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int a[N];
int lg[N];
int st1[N][25],st2[N][25];
void init(){
    lg[1]=0;
    for(int i=2;i<N;i++)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)st1[i][0]=st2[i][0]=a[i];
    for(int k=1;k<=20;k++){
        for(int i=1;i<=n&&i+(1<<k)-1<=n;i++){
            st1[i][k]=max(st1[i][k-1],st1[i+(1<<(k-1))][k-1]);
            st2[i][k]=min(st2[i][k-1],st2[i+(1<<(k-1))][k-1]);
        }
    }
}
int query_max(int l,int r){
    int k=lg[r-l+1];
    return max(st1[l][k],st1[r-(1<<k)+1][k]);
}
int query_min(int l,int r){
    int k=lg[r-l+1];
    return min(st2[l][k],st2[r-(1<<k)+1][k]);
}
int ans[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    init();
    memset(ans,0x3f,sizeof ans);
    for(int c=1;c<=1000000;c=ceil(c*1.06)){
        for(int l=1,r=1;l<=n;l++){
            while(r<=n&&query_max(l,r)-query_min(l,r)<=c)r++;
            ans[r-l]=min(ans[r-l],query_max(l,r-1)-query_min(l,r-1));
        }
    }
    for(int i=2;i<=n;i++){
        ans[i]=(ans[i]==0x3f3f3f3f?ans[i-1]:ans[i]);
        cout<<ans[i]<<"\n";
    }
}