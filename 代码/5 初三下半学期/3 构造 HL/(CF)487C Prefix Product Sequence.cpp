#include <bits/stdc++.h>
#define int long long
using namespace std;
int qpow(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
signed main(){
	int n;
	cin>>n;
	if(n==4){cout<<"YES\n1\n3\n2\n4";return 0;}
	for(int i=2;i*i<=n;i++)if(n%i==0){puts("NO");return 0;}
	puts("YES");
	cout<<"1\n";
	for(int i=2;i<n;i++)cout<<i*qpow(i-1,n-2,n)%n<<"\n";
	if(n>1)cout<<n;
}