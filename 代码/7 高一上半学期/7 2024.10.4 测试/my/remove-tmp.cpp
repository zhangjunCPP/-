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
void update(int x,int val,int n){
	priority_queue<pair<int,int>> q;
	a[x]=val;
	dp1[x][x]=val;
	q.push({1,x});
	while(!q.empty()){
		int len=q.top().first,l=q.top().second;
		int r=l+len-1;
		q.pop();
		for(int i=1;i<l;i++){
			vis[i][r]=false;
			if(vis[i][l-1]&&dp1[i][l-1]==dp1[l][r]&&dp1[i][r]<dp1[l][r]+1){
				dp1[i][r]=dp1[l][r]+1;
				vis[i][r]=true;
				q.push({r-l+1,i});
			}
		}
		for(int i=r+1;i<=n;i++){
			vis[l][i]=false;
			if(vis[r+1][i]&&dp1[r+1][i]==dp1[l][r]&&dp1[l][i]<dp1[l][r]+1){
				dp1[l][i]=dp1[l][r]+1;
				vis[l][i]=true;
				q.push({i-l+1,l});
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
void print(int n){
	for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)cout<<dp1[i][j]<<" ";cout<<"\n";}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("remove2.in","r",stdin);
	freopen("remove2.ans","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	solve(n);
	print(n);
	int q;
	cin>>q;
	int tot=0;
	while(q--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1)cout<<calc(l,r)<<"\n";
		else a[l]=r,solve(n),print(n);
	}
}