#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
int sum[5][N][N];
void add(int opt,int x_1,int y_1,int x_2,int y_2,int w){
	sum[opt][x_1][y_1]+=w;
	sum[opt][x_2+1][y_2+1]+=w;
	sum[opt][x_1][y_2+1]-=w;
	sum[opt][x_2+1][y_1]-=w;
}
int f(int x){return x*(x-1)/2;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int s=0;
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		int x_1,y_1,x_2,y_2,w;
		cin>>x_1>>y_1>>x_2>>y_2>>w;
		s+=w;
		add(0,x_1,y_1,x_2,y_2,w);
		if(x_1==1&&y_1==1)add(1,x_1,y_1,x_2,y_2,w);
		if(x_2==x&&y_1==1)add(2,x_1,y_1,x_2,y_2,w);
		if(x_1==1&&y_2==y)add(3,x_1,y_1,x_2,y_2,w);
		if(x_2==x&&y_2==y)add(4,x_1,y_1,x_2,y_2,w);
	}
	for(int k=0;k<5;k++)for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)sum[k][i][j]+=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1];
	int ans=-1;
	for(int k=1;k<5;k++)for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)ans=max(ans,f(s-sum[0][i][j])+f(sum[0][i][j]-sum[k][i][j])+f(sum[k][i][j]));
	cout<<ans;
}