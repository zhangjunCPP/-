#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;

void solve(){
	int a,b,n;
	cin>>a>>b>>n;
	int sum=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum+=(b-1);
		b=1;
		b=min(a,b+x);
	}
	sum+=b;
	cout<<sum<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}