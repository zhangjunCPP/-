#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,m;
	cin>>n>>m;
	if(n>m) swap(n,m);
	if(n==1) cout<<(m<=2?m-1:m/2+1)<<"\n";
	else cout<<n+(m-n<=2?m-n:(m-n)/2+1)<<"\n";
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
}