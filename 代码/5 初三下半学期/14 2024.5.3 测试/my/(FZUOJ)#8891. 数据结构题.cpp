#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int a[N];
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[i]=1;
	while(m--){
		int opt;
		cin>>opt;
		if(opt==1)for(int i=1;i<=n;i++)a[i]=(a[i]+a[i-1])%mod;
		else if(opt==2){
			int p,x;
			cin>>p>>x;
			a[p]=(a[p]+x)%mod;
		}
		else{
			int l,r;
			cin>>l>>r;
			int ans=0;
			for(int i=l;i<=r;i++)ans=(ans+a[i])%mod;
			cout<<ans<<"\n";
		}
	}
}