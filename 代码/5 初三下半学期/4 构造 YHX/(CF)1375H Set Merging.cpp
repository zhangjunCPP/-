#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int rev[N];
struct node{
    vector<int>flag;
    map<pair<int,int>,int> mp;
}tree[N*4];
int cnt;
pair<int,int> ans1[N*30];
int ans2[N];
void build(int k,int l,int r){
    for(int i=l;i<=r;i++)tree[k].flag.push_back(rev[i]);
    sort(tree[k].flag.begin(),tree[k].flag.end());
    if(l==r)return;
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
int query(int k,int x,int y){
    int l=lower_bound(tree[k].flag.begin(),tree[k].flag.end(),x)-tree[k].flag.begin();
    int r=upper_bound(tree[k].flag.begin(), tree[k].flag.end(),y)-tree[k].flag.begin()-1;
    if(r<l)return 0;
    if(l==r)return tree[k].flag[l];
    int tmp=tree[k].mp[{l,r}];
    if(tmp)return tmp;
    int ql=query(k<<1,x,y),qr=query(k<<1|1,x,y);
    if(!ql||!qr){
        tree[k].mp[{l,r}]=ql|qr;
        return tree[k].mp[{l,r}];
    }
    ans1[++cnt]={ql,qr};
    tree[k].mp[{l,r}]=cnt;
    return tree[k].mp[{l,r}];
}
int a[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        rev[a[i]]=i;
    }
    cnt=n;
    build(1,1,n);
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        ans2[i]=query(1,l,r);
    }
    cout<<cnt<<"\n";
    for(int i=n+1;i<=cnt;i++)cout<<ans1[i].first<<" "<<ans1[i].second<<"\n";
    for(int i=1;i<=q;i++)cout<<ans2[i]<<" ";
}