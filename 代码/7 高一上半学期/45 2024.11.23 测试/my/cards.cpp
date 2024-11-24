#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,mod=1e9+7;
int a[N];
int sum[N];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(k==1){
		for(int i=1;i<=n;i++)sum[i]=(sum[i-1]+a[i])%mod;
		for(int i=1;i<=n-m+1;i++)cout<<(sum[i+m-1]-sum[i-1]+mod)%mod<<" ";
		return 0;
	}
}