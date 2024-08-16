#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=998244353;
int fac[N],inv[N];
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int A(int n,int m) {
	if(n<m)return 0;
	return fac[n]*inv[n-m]%mod;
}
int lowbit(int x){return x&(-x);}
struct node {
	int n;
	int tree[N];
	void add(int x,int y) {for(int i=x;i<=n;i+=lowbit(i))tree[i]=(tree[i]+y)%mod;}
	int query(int x) {
		int ans=0;
		for(int i=x;i;i-=lowbit(i))ans=(ans+tree[i])%mod;
		return ans;
	}
}tree1,tree2;
int a[N];
int pos[N];
int sum[N];
int ans[N];
int val[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int n,k;
	cin>>n>>k;
	tree1.n=n,tree2.n=n;
	for(int i=1;i<=k;i++)cin>>a[i],pos[a[i]]=i;
	for(int i=1;i<=k;i++)sum[i-1]=tree1.query(a[i]-1),tree1.add(a[i],1);
	for(int i=k-1;i>=0;i--)val[i]=(val[i+1]+(a[i+1]-sum[i]-1)*A(n-i-1,k-i-1)%mod)%mod;
	for(int i=0;i<k;i++) {
		ans[a[i]]=tree2.query(a[i]);
		int tmp=(max(a[i+1]-sum[i]-2,0ll)*(k-i-1)%mod*A(n-i-2,k-i-2)%mod+A(n-i-1,k-i-1)%mod)%mod;
		tree2.add(1,tmp);
		tree2.add(a[i+1],(mod-tmp)%mod);
		tmp=max(a[i+1]-sum[i]-1,0ll)*(k-i-1)%mod*A(n-i-2,k-i-2)%mod;
		tree2.add(a[i+1],tmp);
	}
	ans[a[k]]=tree2.query(a[k]);
	for(int i=1;i<=n;i++)cout<<(pos[i]?(ans[i]+val[pos[i]]+1)%mod:tree2.query(i)%mod)<<"\n";
}