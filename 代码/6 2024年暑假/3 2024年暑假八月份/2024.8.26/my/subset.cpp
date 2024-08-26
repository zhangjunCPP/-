#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5;
const int mod=998244353;
int w[N];
int dp[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	int n,v;
	cin>>n>>v;
	for(int i=1;i<=n;i++)cin>>w[i];
	dp[0]=1;
	for(int i=1;i<=n;i++)for(int j=v;j>=0;j--)dp[j]=(dp[j]*2%mod+(j>=w[i]?dp[j-w[i]]:0))%mod;
	cout<<dp[v];

}
/*
 *dp[i][j][k]:前i个，选j个，得到大小为k的背包的方案数
 *转移时枚举当前选不选，并且使用滚动数组优化空间
 *O(n^3)是容易的
 *如何优化？
 *发现，乘以的2次幂等于未从前面转移的次数，因此只需要将未转移时的系数乘2，放进转移式即可
 */