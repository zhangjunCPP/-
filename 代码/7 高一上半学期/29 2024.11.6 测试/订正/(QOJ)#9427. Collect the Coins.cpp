#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e9;
int n;
struct node{
	int t,x;
}a[N];
bool check(int v){
	int l1=1,r1=INF,l2=1,r2=INF;
	for(int i=1;i<=n;i++){
		l1=max(1ll,l1-(a[i].t-a[i-1].t)*v);
		l2=max(1ll,l2-(a[i].t-a[i-1].t)*v);
		r1=min(INF,r1+(a[i].t-a[i-1].t)*v);
		r2=min(INF,r2+(a[i].t-a[i-1].t)*v);
		if(a[i].x>=l1&&a[i].x<=r1&&a[i].x>=l2&&a[i].x<=r2)l1=min(l1,l2),r1=max(r1,r2),l2=r2=a[i].x;
		else if(a[i].x>=l1&&a[i].x<=r1)l1=r1=a[i].x;
		else if(a[i].x>=l2&&a[i].x<=r2)l2=r2=a[i].x;
		else return false;
	}
	return true;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].t>>a[i].x;
	int l=0,r=INF;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}