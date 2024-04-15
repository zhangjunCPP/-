#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,m;
struct node{
    int ls,rs;
    int fa;
    int dep;
}tree[N];
int tot;
int rt[N];
void build(int &k,int l,int r){
    k=++tot;
    if(l==r){
        tree[k].dep=1,tree[k].fa=l;
        return;
    }
    int mid=(l+r)>>1;
    build(tree[k].ls,l,mid);
    build(tree[k].rs,mid+1,r);
}
int query(int k,int l,int r,int x,int root){
    if(l==r){
        if(tree[k].fa==l)return k;
        else return query(rt[root],1,n,tree[k].fa,root);
    }
    int mid=(l+r)>>1;
    if(x<=mid)return query(tree[k].ls,l,mid,x,root);
    else return query(tree[k].rs,mid+1,r,x,root);
}
int clone(int k){
    tree[++tot]=tree[k];
    return tot;
}
void update_fa(int &k1,int k2,int l,int r,int x,int y){
    k1=clone(k2);
    if(l==r){
        tree[k1].fa=y;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update_fa(tree[k1].ls,tree[k2].ls,l,mid,x,y);
    else update_fa(tree[k1].rs,tree[k2].rs,mid+1,r,x,y);
}
void update_dep(int &k1,int k2,int l,int r,int x,int last){
    if(k1<=last)k1=clone(k2);
    if(l==r){
        tree[k1].dep++;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update_dep(tree[k1].ls,tree[k2].ls,l,mid,x,last);
    else update_dep(tree[k1].rs,tree[k2].rs,mid+1,r,x,last);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    build(rt[0],1,n);
    int last=tot;
    for(int i=1;i<=m;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,y;
            cin>>x>>y;
            rt[i]=rt[i-1];
            int fx=query(rt[i],1,n,x,i);
            int fy=query(rt[i],1,n,y,i);
            if(tree[fx].fa!=tree[fy].fa){
                if(tree[fx].dep<tree[fy].dep)swap(fx,fy);
                update_fa(rt[i],rt[i-1],1,n,tree[fy].fa,tree[fx].fa);
                if(tree[fx].dep==tree[fy].dep)update_dep(rt[i],rt[i-1],1,n,tree[fx].fa,last);
                last=tot;
            }
        }
        else if(opt==2){
            int x;
            cin>>x;
            rt[i]=rt[x];
        }
        else{
            int x,y;
            cin>>x>>y;
            rt[i]=rt[i-1];
            int fx=query(rt[i],1,n,x,i);
            int fy=query(rt[i],1,n,y,i);
            if(tree[fx].fa==tree[fy].fa)cout<<"1\n";
            else cout<<"0\n";
        }
    }
}