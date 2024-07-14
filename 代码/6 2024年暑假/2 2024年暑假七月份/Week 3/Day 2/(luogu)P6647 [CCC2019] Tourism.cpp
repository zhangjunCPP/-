#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int a[N];
int L[N],R[N];
int Max[N];
int dp[N];
int suf[N];
signed main() {
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	int tot=n/k;
	for(int i=1;i<=tot;i++) {
		L[i]=R[i-1]+1;
		R[i]=i*k;
	}
	if(n%k)R[++tot]=n,L[tot]=R[tot-1]+1;
	//预处理每一块的前缀最大值
	for(int i=1;i<=tot;i++) {
		Max[L[i]]=a[L[i]];
		for(int j=L[i]+1;j<=R[i];j++)Max[j]=max(Max[j-1],a[j]);
	}
	//处理第一块
	for(int i=R[1];i>=L[1];i--)suf[i]=max(suf[i+1],Max[i]);
	for(int i=L[1];i<=R[1];i++)dp[i]=Max[i];
	for(int i=2;i<=tot;i++) {
		int j=R[i-1];
		int mx1=0,mx2=0;
		while(j>R[i]-k) {
			mx1=max(mx1,dp[j]+mx2);
			mx2=max(mx2,a[j]);
			j--;
		}
		for(int l=R[i];l>=L[i];l--) {
			mx1=max(mx1,dp[j]+mx2);
			mx2=max(mx2,a[j]);
			dp[l]=max(mx1,Max[l]+suf[j]);
			suf[l]=max(suf[l+1],dp[l]);
			j--;
		}
	}
	cout<<dp[n];
}