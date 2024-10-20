#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10;
const int mod=998244353;
const int INF=1e18;
int a[N];
int b[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=i;
	int ans1=0,ans2=0;
	int cnt=0;
	do{
		int sum1=1,sum2=1;
		int Min=INF,Max=-INF;
		int opt1=1,opt2=1;
		for(int i=1;i<=n;i++){
			Min=min(Min,a[b[i]]);
			Max=max(Max,a[b[i]]);
			if(Min<0)opt1=-opt1;
			if(Max<0)opt2=-opt2;
			sum1=(sum1*llabs(Min))%mod;
			sum2=(sum2*llabs(Max))%mod;
		}
		ans1=(ans1+opt1*sum1+mod)%mod;
		ans2=(ans2+opt2*sum2+mod)%mod;
	}while(next_permutation(b+1,b+n+1));
	cout<<(ans1+mod)%mod<<" "<<(ans2+mod)%mod;
}