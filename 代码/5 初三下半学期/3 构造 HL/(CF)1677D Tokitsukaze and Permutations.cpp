#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int a[N];
void solve(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n-k+1;i<=n;i++)if(a[i]>0){cout<<"0\n";return;}
	int ans=1;
	for(int i=1;i<=k;i++)ans=ans*i%mod;
	for(int i=1;i<=n-k;i++){
		if(a[i]==-1)ans=ans*(k+i)%mod;
		else if(!a[i])ans=ans*(k+1)%mod;
	}
	cout<<ans%mod<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}