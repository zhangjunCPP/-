#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=25;
int n;
int a[N];
int sum[N];
int dp[N][N],g[N][N];
vector<pair<int,int>>ans;
bool vis[N];
void modify(int l,int r){
	memset(vis,false,sizeof vis);
	for(int i=l;i<=r;i++)vis[a[i]]=true;
	int tmp=0;
	while(vis[tmp])tmp++;
	for(int i=l;i<=r;i++)a[i]=tmp;
	ans.push_back({l,r});
}
bool check(int l,int r){
	for(int i=l;i<=r;i++)if(a[i])return true;
	return false;
}
void calc(int l,int r){
	if(l>r)return;
	if(l==r){
		while(a[l]!=1)modify(l,r);
		return;
	}
	calc(l,r-1);modify(l,r);modify(l,r-1);calc(l,r-1);
}
void solve(int l,int r){
	if(g[l][r]==0){
		if(sum[r]-sum[l-1]<(r-l+1)*(r-l+1)){   
			while(check(l,r))modify(l,r);
			calc(l,r-1);modify(l,r);
		}
		return;
	}
	solve(l,g[l][r]);
	solve(g[l][r]+1,r);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	for(int len=1;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			dp[l][r]=max(sum[r]-sum[l-1],len*len);
			for(int k=l;k<r;k++)if(dp[l][r]<dp[l][k]+dp[k+1][r])dp[l][r]=dp[l][k]+dp[k+1][r],g[l][r]=k;
		}
	}
	solve(1,n);
	cout<<dp[1][n]<<" "<<ans.size()<<"\n";
	for(auto i:ans)cout<<i.first<<" "<<i.second<<"\n";
}