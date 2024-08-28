#include<bits/stdc++.h>
#define CHECKANS false
using namespace std;
const int N=2e5+10;
struct node {
	int l,r,id;
}a[N];
bool cmp(const node&x,const node&y){
	if(x.l==y.l)return x.r>y.r;
	return x.l<y.l;
}
struct node2 {
	int sum1,sum2;
	node2 operator+(const node2&oth)const {
		node2 ans={};
		ans.sum1=sum1+oth.sum1;
		ans.sum2=sum2+oth.sum2;
		return ans;
	}
}tree[N*4];
int ls(int k){return k<<1;}
int rs(int k){return k<<1|1;}
void modify(int k,int l,int r,int x,int val) {
	if(l==r) {
		if(val==1)tree[k].sum1=1;
		else tree[k].sum2=1;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls(k),l,mid,x,val);
	else modify(rs(k),mid+1,r,x,val);
	tree[k]=tree[ls(k)]+tree[rs(k)];
}
node2 query(int k,int l,int r,int x,int y) {
	if(x>r||y<l)return {};
	if(x<=l&&y>=r)return tree[k];
	int mid=(l+r)>>1;
	node2 ans={};
	if(x<=mid)ans=ans+query(ls(k),l,mid,x,y);
	if(y>mid)ans=ans+query(rs(k),mid+1,r,x,y);
	return ans;
}
int ans[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	if(CHECKANS)cout<<n<<" "<<m<<"\n";

	for(int i=1;i<=m;i++) {
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	if(CHECKANS)for(int i=1;i<=m;i++)cout<<a[i].l<<" "<<a[i].r<<"\n";

	sort(a+1,a+m+1,cmp);
	// for(int i=1;i<=m;i++)cout<<a[i].l<<" "<<a[i].r<<" "<<a[i].id<<"\n";
	for(int i=1;i<=m;i++) {
		if(a[i].r-a[i].l+1<=2)ans[a[i].id]=1;
		else {
			// cout<<"i="<<i<<":  ";
			node2 tmp=query(1,1,n,a[i].l+1,a[i].r-1);
			if(tmp.sum1&&tmp.sum2){puts("IMPOSSIBLE");return 0;}
			// cout<<tmp.sum1<<" "<<tmp.sum2<<"\n";
			ans[a[i].id]=(tmp.sum1==0?1:0);
			modify(1,1,n,a[i].r,ans[a[i].id]);
		}
	}
	// cout<<"\n";
	for(int i=1;i<=m;i++)cout<<(ans[i]?'N':'S')<<"\n";
}
/*
 *排序后贪心找？
 *线段树维护每个城市是否被右端点覆盖，看看他区间内是否有其他的右端点。
 *应该就是这样
 *对了
 */