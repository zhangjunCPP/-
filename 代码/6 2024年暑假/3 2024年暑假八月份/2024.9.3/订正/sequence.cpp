#include <bits/stdc++.h>
#define int long long
const int N=1e6+10;
const int mod=998244353;
using namespace std;
int n;
int a[N];
int lowbit(int x){return x&(-x);}
int tree1[N];
void add1(int x,int v){for(int i=x;i<=n;i+=lowbit(i))tree1[i]=(tree1[i]+v)%mod;}
int query1(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))sum=(sum+tree1[i])%mod;
	return sum%mod;
}
int tree2[N];
void add2(int x,int v){
	for(int i=x;i;i-=lowbit(i)) tree2[i]=(tree2[i]+v)%mod;
}
int query2(int x){
	int sum=0;
	for(int i=x;i<=n;i+=lowbit(i))sum=(sum+tree2[i])%mod;
	return sum%mod;
}
void solve(){
	memset(tree1,0,sizeof tree1);
	memset(tree2,0,sizeof tree2);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=n;i;i--){
		int x=query1(a[i])+1,y=query2(a[i])+1;
		ans=(ans+x*y%mod)%mod;
		add1(a[i],x);
		add2(a[i],y);
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}