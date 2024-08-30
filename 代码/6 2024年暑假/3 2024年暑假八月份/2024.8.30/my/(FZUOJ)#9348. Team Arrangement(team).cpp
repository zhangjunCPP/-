#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1e9;
int n;
int l[N],r[N];
int w[N];
//-----------
int dp[N];
bool check(int i,int x) {return x>=l[i]&&x<=r[i];}
void solve() {
	int lim=(1<<n);
	for(int S=0;S<lim;S++)dp[S]=-INF;
	dp[0]=0;
	for(int S=1;S<lim;S++) {
		for(int T=(S-1)&S;;T=(T-1)&S) {
			int sum=__builtin_popcount(S)-__builtin_popcount(T);
			bool flag=true;
			for(int j=1;j<=n;j++)if(((S>>(j-1))&1)&&(!((T>>(j-1))&1))&&!check(j,sum)){flag=false;break;}
			if(flag&&dp[T]!=-INF)dp[S]=max(dp[S],dp[T]+w[sum]);
			if(!T)break;
		}
	}
	if(dp[lim-1]==-INF)cout<<"impossible\n";
	else cout<<dp[lim-1];
}
//-------------
int sum[100];
void solve_sub3() {
	for(int i=1;i<=n;i++)sum[l[i]]++;
	int ans=0;
	for(int i=1;i<=n;i++) {
		if(sum[i]%i!=0){cout<<"impossible";exit(0);}
		ans+=sum[i]/i*w[i];
	}
	cout<<ans;
	exit(0);
}
//------------
int dp2[65];
void solve_sub4() {
	for(int i=0;i<=60;i++)dp2[i]=-INF;
	dp2[0]=0;
	for(int i=1;i<=n;i++) {
		for(int j=i;j<=n;j++)dp2[j]=max(dp2[j],dp2[j-i]+w[i]);
	}
	cout<<dp2[n];
	exit(0);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	bool sub3=true,sub4=true;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>l[i]>>r[i];
		if(l[i]!=r[i])sub3=false;
		if(l[i]!=1||r[i]!=n)sub4=false;
	}
	for(int i=1;i<=n;i++)cin>>w[i];
	if(sub3)solve_sub3();
	if(sub4)solve_sub4();
	solve();
}
/*
 *T1
 *sub1 暴力，枚举每个人在哪个团
 *sub2 状压？dp[i][S]表示分成i组，人的集合为S的最大权值和
 *sub3 每个人都只接受一个固定人数的团。因此只需要看接受一个团的人数是否是其人数的整数倍即可
 *sub4 每个人都能接受所有团，就是个多重背包，还不用优化
 *sub5 写个鬼
 */