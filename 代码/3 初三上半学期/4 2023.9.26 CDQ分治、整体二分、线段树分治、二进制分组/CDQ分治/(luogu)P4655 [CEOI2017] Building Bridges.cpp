#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e6+10;
int n;
int dp[N];
int h[N],w[N];
struct node{
	int id,x,y;	
}a[N];
int q[N];
double slope(int x,int y){
	if(a[x].x==a[y].x) return -1e18;
	return 1.0*(a[x].y-a[y].y)/(a[x].x-a[y].x);
}
bool cmp1(node x,node y){return h[x.id]<h[y.id];}
bool cmp2(node x,node y){return x.id<y.id;}
bool cmp3(node x,node y){
	if(x.x==y.x) return x.y>y.y;
	return x.x<y.x;
}
void solve(int l,int r){
	if(l==r){
		a[l].x=h[l];
		a[l].y=dp[l]+h[l]*h[l]-w[l];
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	int L=1,R=0;
	for(int i=l;i<=mid;i++){
		while(L<R&&slope(q[R],q[R-1])>=slope(i,q[R])) R--;
		q[++R]=i;
	}
	sort(a+mid+1,a+r+1,cmp1);
	for(int i=mid+1;i<=r;i++){
		while(L<R&&slope(q[L],q[L+1])<=2*h[a[i].id])L++;
		dp[a[i].id]=min(dp[a[i].id],dp[a[q[L]].id]+w[a[i].id-1]-w[a[q[L]].id]+(h[a[i].id]-h[a[q[L]].id])*(h[a[i].id]-h[a[q[L]].id]));
	}
	sort(a+mid+1,a+r+1,cmp2);
	solve(mid+1,r);
	sort(a+l,a+r+1,cmp3);
}
signed main(){
	memset(dp,0x3f,sizeof dp);
	dp[1]=0;
	cin>>n;
	for(int i=1;i<=n;i++) a[i].id=i; 
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=n;i++) cin>>w[i],w[i]+=w[i-1]; 
	solve(1,n);
	cout<<dp[n];
	return 0;
}
