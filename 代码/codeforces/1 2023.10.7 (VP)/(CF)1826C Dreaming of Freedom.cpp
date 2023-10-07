#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,m;
	cin>>n>>m;
	if(m==1||n==1) {puts("YES");return;}
	int ans=n;
	for(int i=2;i*i<=n;i++) {if(n%i==0) {ans=i;break;}}
	if(ans<=m) puts("NO");
	else puts("YES");
}
signed main(){
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}