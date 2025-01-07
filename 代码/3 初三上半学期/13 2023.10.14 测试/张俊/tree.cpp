#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=1e6+10;
int dp[N];
int a[N],b[N];
int ans;
int n;
bool color[N];
void dfs(int now){
	if(now>=n){
		ans++;
		return;
	}
	if(color[a[now]]==0&&color[b[now]]==0) {
		color[a[now]]=1;
		dfs(now+1);
		color[a[now]]=0;
		color[b[now]]=1;
		dfs(now+1);
		color[b[now]]=0;
	}
	else {
		dfs(now+1);
	}
}
signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n;

	dp[1]=1,dp[2]=2;
	for(int i=3;i<=n;i++) dp[i]=(dp[i-1]+dp[i-2])%mod;
	
	bool flag1=true,flag2=true;
	for(int i=1;i<n;i++){
		cin>>a[i]>>b[i];
		if(a[i]!=1||b[i]!=i+1) flag1=false;
		if(a[i]!=i||b[i]!=i+1) flag2=false;
	}
	if(flag1) cout<<n;
	else if(flag2) cout<<dp[n]%mod;
	else {
		dfs(1);
		cout<<ans;
	}
}
