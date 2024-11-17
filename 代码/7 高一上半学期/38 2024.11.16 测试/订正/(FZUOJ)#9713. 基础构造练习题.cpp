#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=2e9+10;
int check(int mid){
	int val1=mid*(mid-1)/2;
	int tmp=(mid+1)/2;
	int val2=(mid-tmp)*(mid-tmp+1)/2+tmp*(tmp-1)/2;
	return val1-val2;
}
void solve(){
	int x;
	cin>>x;
	int l=1,r=INF,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)>=x)ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(ans%2==0&&x%2==1)ans++;
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}