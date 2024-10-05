#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n;
int col[N];
int a[N];
int ans[N];
int solve(int pos){
	return a[col[pos]]-pos;
}
struct node{
	int Min,lazy;
}tree[N*4];
#define ls k<<1
#define rs k<<1|1
void pushup(int k){tree[k].Min=min(tree[ls].Min,tree[rs].Min);}
void build(int k,int l,int r){
	if(l==r){tree[k].Min=2*n-l+1,tree[k].lazy=0;return;}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(k);
}
void update(int k,int val){
	tree[k].Min+=val;
	tree[k].lazy+=val;
}
void pushdown(int k){
	if(tree[k].lazy){
		update(ls,tree[k].lazy);
		update(rs,tree[k].lazy);
		tree[k].lazy=0;
	}
}
void modify(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){update(k,val);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,val);
	if(y>mid)modify(rs,mid+1,r,x,y,val);
	pushup(k);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("fate.in","r",stdin);
	freopen("fate.out","w",stdout);

	cin>>n;
	if(n&1){cout<<":(";return 0;}
	for(int i=1;i<=n*2;i++){
		cin>>col[i];
		a[col[i]]+=i;
	}
	build(1,1,2*n);
	for(int i=1;i<=n*2;i++){
		if(ans[i])continue;
		int oth=solve(i);
		modify(1,1,2*n,1,i,-2);
		modify(1,1,2*n,1,oth,-2);
		if(tree[1].Min>=0)ans[i]=ans[oth]=1;
		else {
			modify(1,1,2*n,1,i,2);
			modify(1,1,2*n,1,oth,2);
			ans[i]=ans[oth]=2;
		}
	}
	int sum=0;
	for(int i=1;i<=2*n;i++){
		if(ans[i]==1)sum++;
		else sum--;
		if(sum<0){cout<<":(";return 0;}
	}
	if(sum){cout<<":(";return 0;}
	for(int i=1;i<=2*n;i++)cout<<(ans[i]==1?'(':')');

}