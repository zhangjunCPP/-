#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10,INF=1e18;
int n;
struct node{
	int x,opt,y;
}a[N];
// int ans;
// bool vis[N];
// vector<int> v;
// void dfs(int k){
// 	if(k>n){
// 		int sum=0;
// 		int last=-1;
// 		// for(int it:v)cout<<it<<" ";
// 		// cout<<"\n";
// 		for(int it:v){
// 			if(last==-1)last=a[it].x;
// 			else sum+=llabs(a[it].x-last),last=a[it].x;
// 		}
// 		ans=min(ans,sum);
// 		return;
// 	}
// 	for(int i=1;i<=n;i++){
// 		if(vis[i])continue;
// 		if(a[i].opt==1||(a[i].opt==2&&vis[a[i].y])){
// 			vis[i]=true;
// 			v.push_back(i);
// 			dfs(k+1);
// 			v.pop_back();
// 			vis[i]=false;
// 		}
// 	}
// }
int dp[(1<<20)+10][22];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("warehouse.in","r",stdin);
	freopen("warehouse.out","w",stdout);
	cin>>n;
	int Max=-1,Min=INF;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].opt;
		Max=max(Max,a[i].x),Min=min(Min,a[i].x);
		if(a[i].opt==1)a[i].y=-1;
		else cin>>a[i].y;
	}
	if(n<=20){	
		for(int s=0;s<(1<<n);s++)for(int i=1;i<=n;i++)dp[s][i]=INF;
		for(int i=1;i<=n;i++)if(a[i].opt==1)dp[(1<<(i-1))][i]=0;
		for(int s=1;s<(1<<n)-1;s++){
			for(int i=1;i<=n;i++){
				if(!((s>>(i-1))&1)){
					if(a[i].opt==2&&!((s>>(a[i].y-1))&1))continue;
					int t=s|(1<<(i-1));
					for(int j=1;j<=n;j++)if(dp[s][j]!=INF)dp[t][i]=min(dp[t][i],dp[s][j]+llabs(a[i].x-a[j].x));
				}
			}
		}
		int ans=INF;
		for(int i=1;i<=n;i++)ans=min(ans,dp[(1<<n)-1][i]);
		cout<<ans;
		// ans=INF;
		// dfs(1);
		// cout<<ans;
		return 0;
	}
	else {
		cout<<Max-Min;
		return 0;
	}
}