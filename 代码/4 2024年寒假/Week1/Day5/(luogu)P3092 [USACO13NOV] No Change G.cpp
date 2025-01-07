#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int k,n;
int w[N],sum[N];
int c[N];
int dp[N];
int calc(int x,int y){
	int l=y,r=n;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(sum[mid]-sum[y-1]<=x)l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
signed main(){
	cin>>k>>n;
	for(int i=1;i<=k;i++) cin>>w[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+c[i];
	for(int i=0;i<(1<<k);i++) {
		for(int j=1;j<=k;j++){
			if(i&(1<<(j-1))){
				int pre=i^(1<<(j-1));
				int last=calc(w[j],dp[pre]+1);
				if(last==-1) continue;
				dp[i]=max(dp[i],last);
			}
		}
	}
	int ans=-1;
	for(int i=0;i<(1<<k);i++){
		if(dp[i]==n){
			int tmp=0;
			for(int j=1;j<=k;j++) if(!(i&(1<<(j-1)))) tmp+=w[j];
			ans=max(ans,tmp);
		}
	}
	cout<<ans;
}