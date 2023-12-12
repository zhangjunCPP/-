#include<bits/stdc++.h>
using namespace std;
int main() {
	int n,s,k;
	cin>>n>>s>>k;
	int ans=0;
	for(int i=1;i<=n;i++){
		int p,q;
		cin>>p>>q;
		ans+=(p*q);
	}
	if(ans<s)ans+=k;
	cout<<ans;
	return 0;
}
