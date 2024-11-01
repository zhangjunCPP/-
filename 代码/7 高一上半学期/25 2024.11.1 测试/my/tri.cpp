#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7,inv2=(mod+1)>>1;
int a[N];
signed main(){
	int n;
	cin>>n;
	bool flag=true;
	int cnt=0;
	for(int i=0;i<n;i++)cin>>a[i],flag&=(!a[i]),cnt+=(a[i]!=0);
	if(flag){
		if(n==3)cout<<"1";
		else cout<<"0";
		return 0;
	}
	if(n==3){
		int ans=(1+a[0]*a[1]%mod*a[2]%mod)%mod;
		int sum=0;
		for(int i=0;i<n;i++){
			int tmp1=a[(i+1)%n];
			int tmp2=a[(i-1+n)%n];
			ans=(ans+a[i]+(a[i])*(a[i]+1)/2%mod*(tmp1+tmp2+1)%mod)%mod;
			sum=(sum+a[i]*(tmp1+tmp2)%mod)%mod;
		}
		cout<<ans+sum*inv2%mod;
		return 0;
	}
	if(cnt==1){
		for(int i=0;i<n;i++){
			if(a[i]){
				cout<<a[i]*(a[i]-1)/2%mod;
				return 0;
			}
		}
	}
}