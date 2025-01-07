#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
mt19937 Rand(time(NULL));
struct node{
	int ls,rs;
	int val,rnd;
	int id;
	int lazy;
}tree[N];
int tot;
int add(int x){
	tree[++tot].val=1;
	tree[tot].rnd=Rand();
	tree[tot].id=x;
	return tot;
}
void pushup(int k){tree[k].val=tree[tree[k].ls].val+tree[tree[k].rs].val+1;}
void pushdown(int k){
	if(tree[k].lazy){
		tree[tree[k].ls].lazy^=1;
		tree[tree[k].rs].lazy^=1;
		swap(tree[k].ls,tree[k].rs);
		tree[k].lazy=0;
	}
}
void split(int now,int k,int &x,int &y){
	if(!now){x=y=0;return;}
	pushdown(now);
	if(tree[tree[now].ls].val<k){x=now;split(tree[now].rs,k-tree[tree[now].ls].val-1,tree[now].rs,y);}
	else{y=now;split(tree[now].ls,k,x,tree[y].ls);}
	pushup(now);
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
int rt;
void insert(int x){rt=merge(rt,add(x));}
void modify(int l,int r){
	int x,y,z;
	split(rt,l-1,x,y);
	split(y,r-l+1,y,z);
	tree[y].lazy^=1;
	rt=merge(x,merge(y,z));
}
void dfs(int now){
	if(!now)return;
	pushdown(now);
	dfs(tree[now].ls);
	cout<<tree[now].id<<" ";
	dfs(tree[now].rs);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)insert(i);
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		modify(l,r);
	}
	dfs(rt);
}