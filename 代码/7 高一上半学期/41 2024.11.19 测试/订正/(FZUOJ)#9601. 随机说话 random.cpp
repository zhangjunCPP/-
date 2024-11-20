#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
int a[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=n;i>1;i--){
		ans=(ans+a[1]*a[i]%mod*(a[1]+a[i]))%mod;
		a[1]=(a[1]+a[i])%mod;
	}
	cout<<ans;
}