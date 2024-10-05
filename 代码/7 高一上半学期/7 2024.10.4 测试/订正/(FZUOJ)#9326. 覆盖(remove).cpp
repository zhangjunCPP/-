#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int INF=1e9;
struct node{
    int sum;
    vector<pair<int,int>>v;
}tree[N];
int ans;
void insert(node&x,pair<int,int>y){
    if(!x.v.size())x.v.push_back(y);
    else if(x.v.back().first==y.first) x.v.back().second+=y.second;
    else if(x.v.size()<2||(!(x.v[x.v.size()-2].first>x.v.back().first&&y.first>x.v.back().first)))x.v.push_back(y);
    else{
        auto now=x.v.back();
        x.v.pop_back();
        ans=max(ans,now.first+int(log2(now.second)));
        int l=min(x.v.back().first,y.first)-now.first;
        if(((now.second>>l)<<l)==now.second)insert(x,{now.first+l,(now.second>>l)});
        else{
            if(now.second>>l) insert(x,{now.first+l,(now.second>>l)});
            insert(x,{INF,0});
            if(now.second>>l) insert(x,{now.first+l,(now.second>>l)});
        }
        insert(x,y);
    }
}
node operator+(const node&x,const node&y){
    ans=-INF;
    node tmp=x;
    tmp.sum=max(tmp.sum,y.sum);
    for(auto it:y.v) insert(tmp,it);
    tmp.sum=max(tmp.sum,ans);
    return tmp; 
}
#define ls k<<1
#define rs k<<1|1
int a[N];
void build(int k,int l,int r){
    if(l==r){
        tree[k].sum=0;
        tree[k].v.push_back({a[l],1});
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    tree[k]=tree[ls]+tree[rs];
}
void update(int k,int l,int r,int x){
    if(l==r){
        tree[k].sum=0;
        tree[k].v.clear();
        tree[k].v.push_back({a[l],1});
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update(ls,l,mid,x);
    else update(rs,mid+1,r,x);
    tree[k]=tree[ls]+tree[rs];
}
node query(int k,int l,int r,int x,int y){
    if(x<=l&&r<=y) return tree[k];
    int mid=(l+r)>>1;
    if(y<=mid)return query(ls,l,mid,x,y);
    if(x>mid)return query(rs,mid+1,r,x,y);
    return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    int q;
    cin>>q;
    while(q--){
        int opt,l,r;
        cin>>opt>>l>>r;
        if(opt==1){
            node tmp=query(1,1,n,l,r),tmp2;
            ans=tmp.sum;
            insert(tmp2,{INF,1});
            for(auto x:tmp.v)insert(tmp2,x);
            insert(tmp2,{INF,1});
            cout<<ans<<"\n";
        }
        else a[l]=r,update(1,1,n,l);
    }
    return 0;
}