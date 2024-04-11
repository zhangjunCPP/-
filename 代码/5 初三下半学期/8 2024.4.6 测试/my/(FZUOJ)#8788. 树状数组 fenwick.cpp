#include<bits/stdc++.h>
#define int long long
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e6+10;
int calc(int x){
    for(int i=0;i<20;i++)if(x&(1<<i))return 1<<i;
    return -1;
}
int n,m;
int tree[N];
int lazy[N];
void update(int k,int l,int r,int val){
    tree[k]+=val*(r-l+1);
    lazy[k]+=val;
}
void pushdown(int k,int l,int r){
    if(!lazy[k])return;
    int mid=(l+r)>>1;
    update(ls,l,mid,lazy[k]);
    update(rs,mid+1,r,lazy[k]);
    lazy[k]=0;
}
void modify(int k,int l,int r,int x,int y,int val){
    if(x<=l&&y>=r){
        update(k,l,r,val);
        return; 
    }
    pushdown(k,l,r);
    int mid=(l+r)>>1;
    if(x<=mid)modify(ls,l,mid,x,y,val);
    if(y>mid)modify(rs,mid+1,r,x,y,val);
    tree[k]=tree[ls]+tree[rs];
}
int query(int k,int l,int r,int x,int y){
    if(x>r||y<l)return 0;
    if(x<=l&&y>=r)return tree[k];
    pushdown(k,l,r);
    int mid=(l+r)>>1;
    return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
int f[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)f[i]=calc(i);
    for(int i=1;i<=m;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r,v;
            cin>>l>>r>>v;
            for(int j=l;j<=r;j++)modify(1,1,n,j-f[j]+1,j,v);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<query(1,1,n,l,r)<<"\n";
        }
    }
}