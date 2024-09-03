#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000+10,mod=998244353;
int lowbit(int x){return x&(-x);}
struct node {
	int n;
	int tree[N];
	void init(int siz){n=siz;memset(tree,0,sizeof tree);}
	void add(int x,int v) {
		for(int i=x;i<=n;i+=lowbit(i))tree[i]=(tree[i]+v)%mod;
	}
	int query(int x) {
		int ans=0;
		for(int i=x;i;i-=lowbit(i))ans=(ans+tree[i])%mod;
		return ans;
	}
	int query(int l,int r) {return (query(r)-query(l-1)+mod)%mod;}
}tr1[N],tr2[N];
int p[N];
int dp[N][N];
void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=0;
	for(int i=1;i<=n;i++)tr1[i].init(n),tr2[i].init(n);
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++) {
		for(int k=n;k>p[i];k--)dp[p[i]][k]=(dp[p[i]][k]+tr1[k].query(p[i]+1,k))%mod;
		for(int j=p[i]-1;j;j--)dp[j][p[i]]=(dp[j][p[i]]+tr2[j].query(j,p[i]-1))%mod;
		for(int k=n;k>p[i];k--)tr1[k].add(p[i],dp[p[i]][k]),tr2[p[i]].add(k,dp[p[i]][k]);
		for(int j=p[i]-1;j;j--)tr1[p[i]].add(j,dp[j][p[i]]),tr2[j].add(p[i],dp[j][p[i]]);
		dp[p[i]][p[i]]=1;
		tr1[p[i]].add(p[i],dp[p[i]][p[i]]);
		tr2[p[i]].add(p[i],dp[p[i]][p[i]]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)ans=(ans+dp[i][j])%mod;
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}
/*
 *应该也许是原题？
 *当时好像说的是从值域上看？一次插入每一个数？
 *好像记住的就这些了，做个毒，当时考场上也没做出来
 *原个鬼，去死
 *50分O(n^3)
 *树状数组优化到70分O(n^2logn)
 */