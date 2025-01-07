#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int ls,rs;
	int val;
}tree[N*40];
int sta[N],cnt;
int tot;
int add(){return cnt?sta[cnt--]:++tot;}
void del(int k){
	sta[++cnt]=k;
	tree[k].ls=tree[k].rs=tree[k].val=0;
}
void pushup(int k){tree[k].val=tree[tree[k].ls].val+tree[tree[k].rs].val;}
void update(int &k,int l,int r,int x,int y){
	if(!k)k=add();
	if(l==r){tree[k].val+=y;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k].ls,l,mid,x,y);
	else update(tree[k].rs,mid+1,r,x,y);
	pushup(k);
}
int query(int k,int l,int r,int x,int y){
	if(x>r||y<l)return 0;
	if(x<=l&&y>=r)return tree[k].val;
	int mid=(l+r)>>1;
	return query(tree[k].ls,l,mid,x,y)+query(tree[k].rs,mid+1,r,x,y);
}
void merge(int &x,int y,int l,int r){
	if(!x||!y){x|=y;return;}
	if(l==r){tree[x].val+=tree[y].val;return;}
	int mid=(l+r)>>1;
	merge(tree[x].ls,tree[y].ls,l,mid);
	merge(tree[x].rs,tree[y].rs,mid+1,r);
	pushup(x);
	del(y);
}
int ask(int k,int l,int r,int x){
	if(tree[k].val<x)return -1;
	if(l==r)return l;
	int mid=(l+r)>>1;
	int tmp=tree[tree[k].ls].val;
	if(x<=tmp)return ask(tree[k].ls,l,mid,x);
	else return ask(tree[k].rs,mid+1,r,x-tmp);
}
void split(int x,int &y,int k){
	if(!x)return;
	y=add();
	int tmp=tree[tree[x].ls].val;
	if(k>tmp)split(tree[x].rs,tree[y].rs,k-tmp);
	else swap(tree[x].rs,tree[y].rs);
	if(k<tmp)split(tree[x].ls,tree[y].ls,k);
	tree[y].val=tree[x].val-k;
	tree[x].val=k;
}
int rt[N],num=1;

signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		update(rt[1],1,n,i,x);
	}
	for(int i=1;i<=m;i++){
		int opt;
		int x,y,z;
		cin>>opt;
		if(opt==0){
			cin>>x>>y>>z;
			int tmp1= query(rt[x],1,n,1,z),tmp2= query(rt[x],1,n,y,z);
			split(rt[x],rt[++num],tmp1-tmp2);
			int tmp=0;
			split(rt[num],tmp,tmp2);
			merge(rt[x],tmp,1,n);
		}
		else if(opt==1){
			cin>>x>>y;
			merge(rt[x],rt[y],1,n);
		}
		else if(opt==2){
			cin>>x>>y>>z;
			update(rt[x],1,n,z,y);
		}
		else if(opt==3){
			cin>>x>>y>>z;
			cout<<query(rt[x],1,n,y,z)<<"\n";
		}
		else{
			cin>>x>>y;
			cout<<ask(rt[x],1,n,y)<<"\n";
		}
	}
}