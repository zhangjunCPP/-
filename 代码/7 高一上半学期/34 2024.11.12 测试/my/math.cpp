#include<bits/stdc++.h>
#define int long long
using namespace std;
int gcd(int x,int y){
	while(y^=x^=y^=x%=y);
	return x;
}
void solve(){
	int n,m;
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j*i<=m;j++){
			if(gcd(i,j)!=1)continue;
			const int GCD=i+j,a=i*GCD,b=j*GCD;
			if(a>n||b>m)continue;
			ans+=min(n/a,m/b);
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}