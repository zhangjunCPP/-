#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10; 
int a[N];
int s[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	int ans=0;
	int j=0;
	for(int i=1;i<=n;i++){
		int cnt=s[i];
		while(j<=i&&a[j]*i<=cnt) j++;
		ans=max(ans,i-j+1);
	}
	cout<<ans<<"\n";
	
	return 0;
}
