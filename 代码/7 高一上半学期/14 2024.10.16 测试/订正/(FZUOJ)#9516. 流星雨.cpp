#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int INF=1e18;
#define ls (k<<1)
#define rs (k<<1|1)
bool vis[N];
vector<int>tree1[N],tree2[N];
void build(int k,int l,int r){
	tree1[k].push_back(0),tree2[k].push_back(0);
	if(l==r)return;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void modify(int k,int l,int r,int x,int y,int val){
	tree1[k].push_back(val);
	if(x<=l&&y>=r){tree2[k].push_back(val);return;}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,val);
	if(y>mid)modify(rs,mid+1,r,x,y,val);
}
int query(int k,int l,int r,int x,int y){
	while(vis[tree2[k].back()])tree2[k].pop_back();
	if(x<=l&&y>=r){
		while(vis[tree1[k].back()])tree1[k].pop_back();
		return tree1[k].back();
	}
	int ans=tree2[k].back();
	int mid=(l+r)>>1;
	if(x<=mid)ans=max(ans,query(ls,l,mid,x,y));
	if(y>mid)ans=max(ans,query(rs,mid+1,r,x,y));
	return ans;
}
int a[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	build(1,1,n);
	a[0]=INF;
	for(int i=1;i<=m;i++){
		int opt,l,r,d;
		cin>>opt>>l>>r>>d;
		if(opt==1){
			a[i]=d;
			modify(1,1,n,l,r,i);
		}
		else{
			while(d){
				int id=query(1,1,n,l,r);
				cout<<id<<" ";
				if(d>=a[id]){d-=a[id];a[id]=0;vis[id]=true;}
				else{a[id]-=d;d=0;}
			}
			cout<<"\n";
		}
	}
}