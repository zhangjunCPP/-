#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n;
struct node{
	int ls,rs;
	ll sum;
}tree[N*30];
int tot;
void pushup(int k){tree[k].sum=tree[tree[k].ls].sum+tree[tree[k].rs].sum;}
void update(int &k,int l,int r,int x) {
	if(!k)k=++tot;
	if(l==r){tree[k].sum++;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k].ls,l,mid,x);
	else update(tree[k].rs,mid+1,r,x);
	pushup(k);
}
void merge(int&x,int y,ll&sum1,ll&sum2){
	if(!x||!y){x|=y;return;}
	sum1+=tree[tree[x].rs].sum*tree[tree[y].ls].sum;
	sum2+=tree[tree[x].ls].sum*tree[tree[y].rs].sum;
	merge(tree[x].ls,tree[y].ls,sum1,sum2);
	merge(tree[x].rs,tree[y].rs,sum1,sum2);
	pushup(x);
}
ll ans;
void dfs(int &u){
	int x;
	cin>>x;
	u=0;
	int ls,rs;
	if(!x){
		dfs(ls);
		dfs(rs);
		u=ls;
		ll sum1=0,sum2=0;
		merge(u,rs,sum1,sum2);
		ans+=min(sum1,sum2);
	}
	else update(u,1,n,x);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	int tmp=0;
	dfs(tmp);
	cout<<ans;
}