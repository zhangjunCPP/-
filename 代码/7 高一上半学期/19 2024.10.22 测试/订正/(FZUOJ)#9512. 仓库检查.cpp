#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e18;
int n;
int ans;
struct node{
	int x,opt,y;
}a[N];
int tmp[N],tot;
bool cmp(const node&x,const node&y){return x.x<y.x;}
int d[N];
int dp[N];
void solve(){
	for(int i=0;i<=tot;i++)d[i]=0;
	for(int i=1;i<=n;i++)
		if(a[i].opt==2&&a[i].y>a[i].x)d[a[i].x+1]++,d[a[i].y+1]--;
	for(int i=1;i<=tot;i++)d[i]+=d[i-1];
	dp[1]=0;
	int Min=INF;
	for(int i=2;i<=tot;i++){
		if(d[i])dp[i]=Min+tmp[i]*3;
		else dp[i]=dp[i-1]+(tmp[i]-tmp[i-1]);
		dp[i]=min(dp[i],(tmp[i]-tmp[1])*2);
		Min=min(Min,dp[i]-tmp[i]*3);
	}
	for(int i=1;i<=tot;i++)ans=min(ans,dp[i]+(tmp[tot]-tmp[i])*2);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].opt;
		if(a[i].opt==2)cin>>a[i].y;
		tmp[++tot]=a[i].x;
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i].x=lower_bound(tmp+1,tmp+tot+1,a[i].x)-tmp;
	for(int i=1;i<=n;i++)a[i].y=a[a[i].y].x;
	sort(a+1,a+n+1,cmp);
	ans=INF;
	solve();
	reverse(a+1,a+n+1);
	reverse(tmp+1,tmp+tot+1);
	for(int i=1;i<=n;i++)a[i].x=tot-a[i].x+1,a[i].y=tot-a[i].y+1;
	for(int i=1;i<=tot;i++)tmp[i]=-tmp[i];
	solve();
	cout<<ans;
}