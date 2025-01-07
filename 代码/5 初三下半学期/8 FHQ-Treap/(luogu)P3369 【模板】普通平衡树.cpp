#include<bits/stdc++.h>
using namespace std;
const int N=6e5+10,INF=1e9;
mt19937 Rand(time(NULL));
struct node{
	int ls,rs;
	int val,rnd;
	int siz;
}tree[N];
int tot;
int new_node(int x){
	tree[++tot].val=x;
	tree[tot].rnd=Rand();
	tree[tot].siz=1;
	return tot;
}
void dfs(int now){
	if(!now)return;
	dfs(tree[now].ls);
	cout<<tree[now].val<<" ";
	dfs(tree[now].rs);
}
int ls(int k){return tree[k].ls;}
int rs(int k){return tree[k].rs;}
int rt;
void pushup(int k){
	tree[k].siz=tree[ls(k)].siz+tree[rs(k)].siz+1;
}
void split(int now,int k,int &x,int &y){
	if(!now){x=y=0;return;}
	if(tree[now].val<=k)x=now,split(tree[now].rs,k,tree[now].rs,y);
	else y=now,split(tree[now].ls,k,x,tree[now].ls);
	pushup(now);
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	if(tree[x].rnd<tree[y].rnd){
		tree[x].rs=merge(tree[x].rs,y);
		pushup(x);
		return x;
	}
	else{
		tree[y].ls=merge(x,tree[y].ls);
		pushup(y);
		return y;
	}
}
void insert(int a){
	int x,y;
	split(rt,a,x,y);
	rt=merge(merge(x,new_node(a)),y);
}
void del(int a){
	int x,y,z;
	split(rt,a,x,y);
	split(x,a-1,x,z);
	rt=merge(merge(x,merge(ls(z),rs(z))),y);
}
int get_rank(int a){
	int x,y;
	split(rt,a-1,x,y);
	int ans=tree[x].siz+1;
	rt=merge(x,y);
	return ans;
}
int get_kth(int now,int k){
	while(1){
		if(tree[ls(now)].siz>=k) now=ls(now);
		else if(tree[ls(now)].siz+1==k)return now;
		else k=k-tree[ls(now)].siz-1,now=rs(now);
	}
}
int get_pre(int a){
	int x,y;
	split(rt,a-1,x,y);
	int ans=tree[get_kth(x,tree[x].siz)].val;
	rt=merge(x,y);
	return ans;
}
int get_next(int a){
	int x,y;
	split(rt,a,x,y);
	int ans=tree[get_kth(y,1)].val;
	rt=merge(x,y);
	return ans;
}
int main(){
	int n;
	cin>>n;
	while(n--){
		int opt,x;
		cin>>opt>>x;
		if(opt==1)insert(x);
		else if(opt==2)del(x);
		else if(opt==3)cout<<get_rank(x)<<"\n";
		else if(opt==4)cout<<tree[get_kth(rt,x)].val<<"\n";
		else if(opt==5)cout<<get_pre(x)<<"\n";
		else if(opt==6)cout<<get_next(x)<<"\n";
	}
}