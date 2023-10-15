
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=2e5+10;
int gcd(int x,int y) {
	while(x^=y^=x^=y%=x);
	return y;
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int a[N];
int ANS[505][505];
int ans;
void dfs(int now,int l,int r,int GCD){
	if(now>r) {
		if(GCD==-1) return;
		ans=ans*GCD%mod;
		return;
	} 
	if(GCD==1) return; 
	if(GCD==-1) {
		dfs(now+1,l,r,a[now]);
		dfs(now+1,l,r,GCD);
		return ;
	}
	else{
		dfs(now+1,l,r,gcd(GCD,a[now]));
		dfs(now+1,l,r,GCD);
	} 
}
signed main(){
	freopen("ddickky.in","r",stdin);
	freopen("ddickky.out","w",stdout);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--) {
		ans=1;
		int l,r;
		cin>>l>>r;
		if(n<=500&&ANS[l][r]){
			cout<<ANS[l][r];
		}
		else{
			dfs(l,l,r,-1);
			ANS[l][r]=ans;
			cout<<ans<<"\n";
		}
	}
}
/*
5 2
8 2 8 8 9
1 5
2 4
*/
