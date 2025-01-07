#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{int l,s,p;}a[N];
bool cmp(const node&x,const node&y){return x.s<y.s;}
int q[N];
int dp[105][16005];
int solve(int i,int k){return dp[i-1][k]-a[i].p*k;}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>a[i].l>>a[i].p>>a[i].s;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		int l=1,r=0;
		for(int j=max(0,a[i].s-a[i].l);j<=a[i].s-1;j++){
			while(l<=r&&(solve(i,q[r])<=solve(i,j)))r--;
			q[++r]=j;
		}
		for(int j=1;j<=n;j++){
			dp[i][j]=max({dp[i][j-1],dp[i-1][j]});
			if(j>=a[i].s){
				while(l<=r&&q[l]<j-a[i].l)l++;
				if(l<=r)dp[i][j]=max(dp[i][j],a[i].p*j+solve(i,q[l]));
			}
		}
	}
	cout<<dp[m][n];
	return 0;
}