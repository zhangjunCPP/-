#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e18;
int a[N];
struct node{
	int l,r;
}q[N];
bool cmp(const node&x,const node&y){
	if(x.r==y.r)return x.l<y.l;
	return x.r<y.r;
}
int dp[N];
int que[N],l,r;
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r;
	sort(q+1,q+m+1,cmp);
	int left=0;
	for(int i=1,j=1;i<=n;i++){
		// cout<<"i="<<i<<"\nleft="<<left<<"\n";
		while(l<r&&que[l]<left)l++;
		// for(int k=l;k<=r;k++)cout<<que[k]<<" ";
		// cout<<"\n";
		dp[i]=dp[que[l]]+a[i];
		// cout<<"que[l]="<<que[l]<<"\n";
		while(l<r&&dp[que[r]]>=dp[i])r--;
		que[++r]=i;
		for(;j<=m&&q[j].r<=i;j++)left=max(left,q[j].l);
		// for(int k=l;k<=r;k++)cout<<que[k]<<" ";
		// cout<<"\n";
	}
	// cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";
	// cout<<"\n";
	int ans=INF;
	for(int i=left;i<=n;i++)ans=min(ans,dp[i]);
	cout<<ans<<'\n';
}