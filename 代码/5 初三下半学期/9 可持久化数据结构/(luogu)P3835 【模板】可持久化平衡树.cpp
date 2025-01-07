#include<bits/stdc++.h>
#define ls(k) (tree[k].ls)
#define rs(k) (tree[k].rs)
using namespace std;
const int N=5e5+10,INF=1e9;
mt19937 Rand(time(NULL));
struct node{
	int ls,rs;
	int val,rnd;
	int siz;
}tree[N*50];
int tot;
int new_node(int x){
	tree[++tot].val=x;
	tree[tot].rnd=Rand();
	tree[tot].siz=1;
	return tot;
}
void pushup(int k){tree[k].siz=tree[ls(k)].siz+tree[rs(k)].siz+1;}
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void split(int now,int k,int &x,int &y){
	if(!now){x=y=0;return;}
	if(tree[now].val<=k){x=clone(now);split(rs(now),k,rs(x),y);pushup(x);}
	else{y=clone(now);split(ls(now),k,x,ls(y));pushup(y);}
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	if(tree[x].rnd<tree[y].rnd){
		rs(x)=merge(rs(x),y);
		pushup(x);
		return x;
	}
	else{
		ls(y)=merge(x,ls(y));
		pushup(y);
		return y;
	}
}
int rt[N],cnt;
void insert(int ver,int a){
	int x,y;
	split(rt[ver],a,x,y);
	rt[++cnt]=merge(merge(x,new_node(a)),y);
}
void del(int ver,int a){
	int x,y,z;
	split(rt[ver],a,x,y);
	split(x,a-1,x,z);
	rt[++cnt]=merge(merge(x,merge(ls(z),rs(z))),y);
}
int get_rank(int ver,int a){
	int x,y;
	split(rt[ver],a-1,x,y);
	int ans=tree[x].siz+1;
	rt[++cnt]=merge(x,y);
	return ans;
}
int get_kth(int now,int k){
	while(1){
		if(tree[ls(now)].siz>=k) now=ls(now);
		else if(tree[ls(now)].siz+1==k)return now;
		else k=k-tree[ls(now)].siz-1,now=rs(now);
	}
}
int get_pre(int ver,int a){
	int x,y;
	split(rt[ver],a-1,x,y);
	int ans=tree[get_kth(x,tree[x].siz)].val;
	rt[++cnt]=merge(x,y);
	return ans;
}
int get_next(int ver,int a){
	int x,y;
	split(rt[ver],a,x,y);
	int ans=tree[get_kth(y,1)].val;
	rt[++cnt]=merge(x,y);
	return ans;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	while(n--){
		int ver,opt,x;
		cin>>ver>>opt>>x;
		if(opt==1)insert(ver,x);
		else if(opt==2)del(ver,x);
		else if(opt==3)cout<<get_rank(ver,x)<<"\n";
		else if(opt==4){cout<<tree[get_kth(rt[ver],x)].val<<"\n";rt[++cnt]=rt[ver];}
		else if(opt==5)cout<<get_pre(ver,x)<<"\n";
		else if(opt==6)cout<<get_next(ver,x)<<"\n";
	}
}