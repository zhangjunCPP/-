#include<bits/stdc++.h>
#define int long long
#define ls(k) (tree[k].ls)
#define rs(k) (tree[k].rs)
using namespace std;
const int N=2e5+10;
mt19937 Rand(time(NULL));
struct node{
    int val;
    int ls,rs;
    int siz,rnd;
    int lazy;
    int sum;
}tree[N*100];
int tot;
int clone(int k){
    tree[++tot]=tree[k];
    return tot;
}
void pushup(int k){
    tree[k].siz=tree[ls(k)].siz+tree[rs(k)].siz+1;
    tree[k].sum=tree[ls(k)].sum+tree[rs(k)].sum+tree[k].val;
}
void pushdown(int k){
    if(!tree[k].lazy)return;
    if(ls(k))ls(k)=clone(ls(k));
    if(rs(k))rs(k)=clone(rs(k));
    swap(ls(k),rs(k));
    if(ls(k))tree[ls(k)].lazy^=1;
    if(rs(k))tree[rs(k)].lazy^=1;
    tree[k].lazy=0;
}
void split(int now,int k,int &x,int &y){
    if(!now){x=y=0;return;}
    pushdown(now);
    if(k>tree[ls(now)].siz){x=clone(now);split(rs(now),k-tree[ls(now)].siz-1,rs(x),y);pushup(x);}
    else{y=clone(now);split(ls(now),k,x,ls(y));pushup(y);}
}
int merge(int x,int y){
    if(!x||!y)return x+y;
    if(tree[x].rnd<tree[y].rnd){
        pushdown(x);
        tree[x].rs=merge(tree[x].rs,y);
        pushup(x);
        return x;
    }
    else{
        pushdown(y);
        tree[y].ls=merge(x,tree[y].ls);
        pushup(y);
        return y;
    }
}
int rt[N],cnt;
int new_node(int a){
    tree[++tot].rnd=Rand();
    tree[tot].siz=1;
    tree[tot].val=tree[tot].sum=a;
    return tot;
}
void insert(int ver,int p,int a){
    int x,y;
    split(rt[ver],p,x,y);
    rt[++cnt]=merge(merge(x,new_node(a)),y);
}
void del(int ver,int p){
    int x,y,z;
    split(rt[ver],p,x,y);
    split(x,p-1,x,z);
    rt[++cnt]=merge(x,y);
}
void modify(int ver,int l,int r){
    int x,y,z;
    split(rt[ver],r,x,y);
    split(x,l-1,x,z);
    tree[z].lazy^=1;
    rt[++cnt]=merge(merge(x,z),y);
}
int query(int ver,int l,int r){
    int x,y,z;
    split(rt[ver],r,x,y);
    split(x,l-1,x,z);
    int ans=tree[z].sum;
    rt[++cnt]=merge(merge(x,z),y);
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    int lastans=0;
    for(int i=1;i<=n;i++){
        int ver,opt;
        cin>>ver>>opt;
        if(opt==1){
            int p,a;cin>>p>>a;p^=lastans,a^=lastans;
            insert(ver,p,a);
        }
        else if(opt==2){
            int p;cin>>p;p^=lastans;
            del(ver,p);
        }
        else if(opt==3){
            int l,r;cin>>l>>r;l^=lastans,r^=lastans;
            modify(ver,l,r);
        }
        else{
            int l,r;cin>>l>>r;l^=lastans,r^=lastans;
            cout<<(lastans=query(ver,l,r))<<"\n";
        }
    }
}