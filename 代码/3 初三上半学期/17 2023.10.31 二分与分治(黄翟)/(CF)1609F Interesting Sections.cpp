#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
ll popc(ll x){return __builtin_popcountll(x);}
int n;
ll a[N];
ll ans;

int sum[N];
int sum1[64],sum2[64];
int sum3[64],sum4[64];
void solve(int l,int r){
	if(l==r){
		ans++;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	memset(sum1,0,sizeof sum1);
	memset(sum2,0,sizeof sum2);
	memset(sum3,0,sizeof sum3);
	memset(sum4,0,sizeof sum4);
	sum[mid]=0;
	ll Max=-1,Min=1e18+10;
	for(int i=mid+1;i<=r;i++){
		Max=max(Max,a[i]);
		Min=min(Min,a[i]);
		sum[i]=sum[i-1]+(popc(Max)==popc(Min));
	}

	Max=-1,Min=1e18+10;
	ll mx1=-1,mx2=-1;
	ll mn1=1e18+10,mn2=1e18+10;
	int p1=mid,p2=mid;
	for(int i=mid;i>=l;i--) {
		Max=max(Max,a[i]);
		Min=min(Min,a[i]);
		while(p1<r&&Min<=min(mn1,a[p1+1])&&Max>=max(mx1,a[p1+1])){
			p1++;
			mn1=min(mn1,a[p1]);
			mx1=max(mx1,a[p1]);
			sum1[popc(mn1)]++;sum2[popc(mx1)]++;
		}
		while(p2<r&& (Min<=min(mn2,a[p2+1])||Max>=max(mx2,a[p2+1])) ){
			p2++;
			mn2=min(mn2,a[p2]);
			mx2=max(mx2,a[p2]);
			sum3[popc(mn2)]++;sum4[popc(mx2)]++;
		}
		ans+=(popc(Max)==popc(Min))*(p1-mid)+sum[r]-sum[p2];
		if(Min<=mn2) ans+=sum4[popc(Min)]-sum2[popc(Min)];
		else ans+=sum3[popc(Max)]-sum1[popc(Max)];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	solve(1,n);
	cout<<ans;
}
