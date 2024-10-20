#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=2e4+10;
int c[N];
bitset<N>dp[M]/*dp[i][j]:以字符i为结尾的长度为j的子序列个数*/,sum;
bool check(int x,int y){
	//C(x,y)的奇偶性
	//C(x,y)%2=C(x%2,y%2)*C(x/2,y/2)
	//C(0,0)=C(1,0)=C(1,1)=1,C(0,1)=0
	//所以当 (x&y)=y 时，C(x,y)%2=1
	return (x&y)==y;
}
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=m;i++)dp[i].reset();
	sum.reset();
	for(int i=1;i<=n;i++){
		sum^=dp[c[i]];
		dp[c[i]]=(sum<<1);
		dp[c[i]].set(1);
		sum^=dp[c[i]];
	}
	bool ans=0;
	for(int i=1;i<=n;i++)ans^=(check(n-1,i-1)*sum[i]);
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}