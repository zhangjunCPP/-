//100pts
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,b[1000006],ans[1000006];
int op,l,r,MOd;
int C,d;
struct Bart{
	int I,m;
	void ini(int MOd){m=MOd;I=(1ll<<62)/m;}
	int operator()(int x){
		int tp=x-((__int128)x*I>>62)*m;
		while(tp>=m)tp-=m;
		return tp;
	}
}getmod;
struct P{
	int l,r,tagg;
	int col,all,tag,t,tagh;
	int sum;
}tree[4000015];
void addv(int t,int val){
	tree[t].tag=getmod(tree[t].tag+val);
	tree[t].sum=getmod(tree[t].sum+(tree[t].r-tree[t].l+1)*val);
	tree[t].tagh=getmod(tree[t].tagh+val*tree[t].t);
	return;
}
void addt(int t,int ti){
	tree[t].all=getmod(tree[t].all+ti*tree[t].sum);
	tree[t].t=getmod(tree[t].t+ti);
	return;
}
void pushup(int t){
	tree[t].all=getmod(tree[t*2].all+tree[t*2+1].all);
	tree[t].sum=getmod(tree[t*2].sum+tree[t*2+1].sum);
	tree[t].col=(tree[t*2].col==tree[t*2+1].col)?tree[t*2].col:0;
	return;
}
void cls(int t){
	tree[t].tagg=1;
	tree[t].tagh=tree[t].all=tree[t].t=0;
	return;
}
void pd(int t){
	int f=t/2;
	P&x=tree[t];
	if(tree[f].tagg)cls(t);
	if(tree[f].tag)addv(t,tree[f].tag);
	if(tree[f].tagh){
		x.all=getmod(x.all-tree[f].tagh*(x.r-x.l+1));
		x.tagh=getmod(x.tagh+tree[f].tagh);
	}
	if(tree[f].t)addt(t,tree[f].t);
	if(tree[f].col)x.col=tree[f].col;
	return;
}
void pushdown(int t){
	pd(2*t),pd(2*t+1);
	tree[t].tagg=tree[t].tag=tree[t].tagh=tree[t].t=0;
	return;
}
void build(int t,int l,int r){
	tree[t].l=l,tree[t].r=r;
	if(l==r){
		tree[t].col=b[l];
		return ;
	}
	int mid=tree[t].l+tree[t].r>>1;
	build(t*2,l,mid);
	build(t*2+1,mid+1,r);
	pushup(t);
	return;
}
void change(int t,int x,int y,int c){
	if(tree[t].l>=x and tree[t].r<=y){
		tree[t].col=c;
		return ;
	}
	pushdown(t);
	int mid=tree[t].l+tree[t].r>>1;
	if(x<=mid)change(t*2,x,y,c);
	if(y>mid)change(t*2+1,x,y,c);
	pushup(t);
	return;
}
void modify(int t,int x,int y,int c){
	if(tree[t].l>=x and tree[t].r<=y){
		addv(t,c);
		return ;
	}
	pushdown(t);
	int mid=tree[t].l+tree[t].r>>1;
	if(x<=mid)modify(t*2,x,y,c);
	if(y>mid)modify(t*2+1,x,y,c);
	pushup(t);
	return;
}
void query(int t,int x,int y){
	if(tree[t].l>=x and tree[t].r<=y and tree[t].col){
		ans[tree[t].col]=getmod(ans[tree[t].col]+tree[t].all);
		cls(t);
		return ;
	}
	pushdown(t);
	int mid=tree[t].l+tree[t].r>>1;
	if(x<=mid)query(t*2,x,y);
	if(y>mid)query(t*2+1,x,y);
	pushup(t);
	return;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>C;
	cin>>n>>q>>MOd;
	getmod.ini(MOd);
	for(int i=1;i<=n;++i)cin>>b[i];
	build(1,1,n);
	for(int i=1;i<=q;++i){
		cin>>op>>l>>r>>d;
		if(op==2){
			query(1,l,r);
			change(1,l,r,d);
		}else modify(1,l,r,d);
		addt(1,1);
	}
	query(1,1,n);
	for(int i=1;i<=n;++i)
		cout<<(MOd-(ans[i]+MOd)%MOd)%MOd<<' ';
	cout<<'\n';
	return 0;
}