#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int o,a[N],mx[N][21],n;
ll ans;
int Max(int x,int y) {return a[x]>a[y]?x:y;}
int ask(int l,int r)
{
	if(l>r) return 0;
	int x=__lg(r-l+1); return Max(mx[l][x],mx[r-(1<<x)+1][x]);
}
void solve(int l,int r)
{
	if(l==r) return;
	int mx1=ask(l,r);
	int mx2=Max(ask(l,mx1-1),ask(mx1+1,r));
	ans+=a[mx1]-a[mx2];
	if(mx1<mx2) solve(l,mx1),solve(mx1+1,r);
	else solve(l,mx1-1),solve(mx1,r);
}
void work()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],mx[i][0]=i;
	for(int j=1;1<<j<=n;j++)
		for(int i=1;i<=n-(1<<j)+1;i++) mx[i][j]=Max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
	ans=0,solve(1,n);
	cout<<ans<<'\n';
}
signed main()
{

	ios::sync_with_stdio(0),cin.tie(0);
	int t; cin>>o>>t; while(t--) work();
	return 0;
}