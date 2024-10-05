#include<bits/stdc++.h>
using namespace std;
const int N=5000+10;
int a[N];
bool vis[N][N];
int dp1[N][N];
void solve(int n){
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)vis[i][j]=dp1[i][j]=0;
	for(int i=1;i<=n;i++)vis[i][i]=true,dp1[i][i]=a[i];
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(int k=l;k<r;k++){
				if(vis[l][k]&&vis[k+1][r]&&dp1[l][k]==dp1[k+1][r]){
					vis[l][r]=true;
					dp1[l][r]=max(dp1[l][r],dp1[l][k]+1);
				}
			}
		}
	}
}
int dp2[N];
int calc(int l,int r){
	int n=r-l+1;
	for(int i=0;i<=r;i++)dp2[i]=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)if(vis[j+l-1][i+l-1])dp2[i]=max(dp2[i],max(dp2[j-1],dp1[j+l-1][i+l-1]));
	return dp2[n];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("remove.in","r",stdin);
	freopen("remove.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	solve(n);
	int q;
	cin>>q;
	int tot=0;
	while(q--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1)cout<<calc(l,r)<<"\n";
		else a[l]=r,solve(n);
	}
}