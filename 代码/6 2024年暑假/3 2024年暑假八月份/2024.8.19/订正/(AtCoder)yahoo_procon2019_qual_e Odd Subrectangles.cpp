#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
const int mod=998244353;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
bitset<N>p[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	int ans=1;
	for(int i=1;i<=n;i++) {
		bitset<N>now;
		for(int j=1;j<=m;j++) {
			int x;
			cin>>x;
			now[j]=x;
		}
		bool flag=true;
		for(int j=1;j<=m;j++) {
			if(!now[j])continue;
			if(!p[j][j]) {
				p[j]=now;
				flag=false;
				break;
			}
			now^=p[j];
		}
		if(flag)ans=ans*2%mod;
	}
	cout<<(qpow(2,n)-ans+mod)%mod*qpow(2,m-1)%mod;
}