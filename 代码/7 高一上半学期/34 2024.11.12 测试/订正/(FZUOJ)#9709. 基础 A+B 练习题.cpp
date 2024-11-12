#include<bits/stdc++.h>
#define uint unsigned int
using namespace std;
const int N=5e5+10;
uint a[N],b[N],ans[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int j=0;j<32;j++){
		for(int i=1;i<=n;i++){
			ans[i]|=(((a[i]^ans[i-1])+(b[i]^ans[i-1]))>>j&1)<<j;
		}
		ans[0]=ans[n];
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}