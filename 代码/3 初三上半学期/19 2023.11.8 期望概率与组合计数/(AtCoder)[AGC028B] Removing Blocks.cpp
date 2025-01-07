#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e6+5;
int inv[N];
int s[N];
int a[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	inv[1]=1;
	for(int i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++) s[i]=(s[i-1]+inv[i])%mod;
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+(s[i]+s[n-i+1]-1+mod)%mod*a[i]%mod)%mod;
	for(int i=1;i<=n;i++) ans=ans*i%mod;
	cout<<ans;
	return 0;
}