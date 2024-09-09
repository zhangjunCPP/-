#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int Max,lazy;
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void pushup(int k){tree[k].Max=max(tree[ls].Max,tree[rs].Max);}
void update(int k,int val){
	tree[k].lazy+=val;
	tree[k].Max+=val;
}
void pushdown(int k){
	if(tree[k].lazy){
		update(ls,tree[k].lazy);
		update(rs,tree[k].lazy);
		tree[k].lazy=0;
	}
}
void modify(int k,int l,int r,int x,int y,int val) {
	if(x<=l&&y>=r){update(k,val);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,val);
	if(y>mid)modify(rs,mid+1,r,x,y,val);
	pushup(k);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	int now=0;
	while(q--) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		while(now<b){now++;modify(1,1,n,now,now,now);}
		modify(1,1,n,a,b,c);
		if(d)cout<<tree[1].Max-1<<"\n";
	}
}