#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e18;
const int N=3e5+10;
int n,m;
int p[N];
int dp[N];

int tree[N];
int lowbit(int x){return x&-x;}
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i)) tree[i]+=val;}
int ask(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)) ans+=tree[i];
	return ans;
}
int L=1,R=0;
int sum=0;

int calc(int x,int y){
	while(L>x) {
		--L;
		add(p[L],1);
		sum+=ask(p[L]-1);
	}
	while(R<y){
		++R;
		add(p[R],1);
		sum+=R-L-ask(p[R]-1);
	}
	while(L<x){
		sum-=ask(p[L]-1);
		add(p[L],-1);
		L++;
	}
	while(R>y){
		sum-=R-L-ask(p[R]-1);
		add(p[R],-1);
		R--;
	}
	return sum;
}
void solve(int l,int r,int x,int y){
	if(l>r) return;
	int mid=(l+r)>>1;
	int Min=INF,id;
	for(int i=x;i<=min(mid,y);i++) {
		int tmp=calc(i+1,mid)+dp[i];
		if(Min>tmp) Min=tmp,id=i; 
	}
	dp[mid]=min(dp[mid],Min+m);
	solve(l,mid-1,x,id);
	solve(mid+1,r,id,y);
}
void cdq(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);
	solve(mid+1,r,l,mid);
	cdq(mid+1,r);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) dp[i]=calc(1,i)+m;
	cdq(1,n);
	cout<<dp[n];
}
