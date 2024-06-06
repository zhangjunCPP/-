#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int f(int x){return x*(x-1)/2;}
struct node{
	int x_1,y_1,x_2,y_2;
	int c;
}a[N];
int sum[1005][1005];
int n,x,y;
int ans;
void dfs(int k){
	if(k>n){
		int tmp=0;
		for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)tmp+=f(sum[i][j]);
		ans=max(ans,tmp);
		return;
	}
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			if(i>=a[k].x_1&&i<=a[k].x_2&&j>=a[k].y_1&&j<=a[k].y_2)continue;
			sum[i][j]+=a[k].c;
			dfs(k+1);
			sum[i][j]-=a[k].c;
		}
	}

}
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)cin>>a[i].x_1>>a[i].y_1>>a[i].x_2>>a[i].y_2>>a[i].c;
	dfs(1);
	cout<<ans;
}