#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
struct node{
	int val,mx,mn,ans;
}a[N+10];
int n,m;
//dp[i]=max{dp[j]}+1    j<i&&a[j].mx<=a[i].val&&a[j].val<=a[i].mn 
int tree[N+10];
int lowbit(int x){return x&(-x);}
void add(int x,int y){for(int i=x;i<=N;i+=lowbit(i)) tree[i]=max(tree[i],y);}
int query(int x){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i)) ans=max(ans,tree[i]);
	return ans;
}
void clear(int x){for(int i=x;i<=N;i+=lowbit(i)) tree[i]=0;}

int tmp[N];

bool cmp1(int x,int y){
	return a[x].mx<a[y].mx;
}
bool cmp2(int x,int y){
	return a[x].val<a[y].val;
}
void solve(int l,int r){
	if(l==r){
		a[l].ans=max(a[l].ans,1);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	
	for(int i=l;i<=r;i++)tmp[i]=i;
	sort(tmp+l,tmp+mid+1,cmp1);
	sort(tmp+mid+1,tmp+r+1,cmp2); 
	
	int j=l;
	for(int i=mid+1;i<=r;i++) {
		while(j<=mid&&a[tmp[j]].mx<=a[tmp[i]].val) {
			add(a[tmp[j]].val,a[tmp[j]].ans);
			j++;
		}
		a[tmp[i]].ans=max(a[tmp[i]].ans,query(a[tmp[i]].mn)+1);
	}
	for(int i=l;i<j;i++) clear(a[tmp[i]].val);
	solve(mid+1,r);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i].val;
		a[i].mx=a[i].mn=a[i].val;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		a[x].mx=max(a[x].mx,y);
		a[x].mn=min(a[x].mn,y);
	}
	solve(1,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,a[i].ans);
	}
	cout<<ans;
	return 0;
}
