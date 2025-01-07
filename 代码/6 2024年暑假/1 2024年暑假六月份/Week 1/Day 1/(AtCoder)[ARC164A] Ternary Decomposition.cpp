#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,k;
	cin>>n>>k;
	int cnt=0;
	int sum=0;
	while(n)sum+=n%3,n/=3;
	if(k>=sum&&((k-sum)%2==0))puts("Yes");
	else puts("No");
	
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}