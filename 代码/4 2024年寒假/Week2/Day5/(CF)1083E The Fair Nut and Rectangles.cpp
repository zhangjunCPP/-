#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
struct node{int x,y,val;}a[N];
bool cmp(const node&x,const node&y){return x.x<y.x;}
int dp[N];
int X(int i){return a[i].x;}
int Y(int i){return dp[i];}
double slope(int i,int j){
	if(X(i)==X(j)) return Y(j)>=Y(i)?1e18:-1e18;
	return (1.0*(Y(i)-Y(j)))/(1.0*(X(i)-X(j)));
}
int l,r,q[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y>>a[i].val;
	sort(a+1,a+n+1,cmp);
	l=1,r=1;
	q[1]=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		while(l<r&&slope(q[l],q[l+1])>=a[i].y)l++;
		int j=q[l];
		dp[i]=dp[j]+a[i].x*a[i].y-a[j].x*a[i].y-a[i].val;
		ans=max(ans,dp[i]);
		while(l<r&&slope(q[r-1],q[r])<=slope(q[r],i))r--;
		q[++r]=i;
	}
	cout<<ans;

	return 0;
}