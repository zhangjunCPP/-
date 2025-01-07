#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int x_1,y_1,x_2,y_2,col;
}a[N];
bool cmp(const node &a,const node &b){
	if(a.x_1!=b.x_1)return a.x_1<b.x_1;
	return a.y_1<b.y_1;
}
vector<int> v[N];
int dp[N][25];
bool check(int S,int i){
	if(!(S&(1<<(i-1)))) return false;
	for(int j:v[i])if(!(S&(1<<(j-1))))return false;
	return true;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x_1>>a[i].y_1>>a[i].x_2>>a[i].y_2>>a[i].col;
		a[i].x_1++,a[i].y_1++;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			if(a[i].x_1==a[j].x_2+1&&((a[i].y_1>=a[j].y_1&&a[i].y_1<=a[j].y_2)||(a[i].y_2>=a[j].y_1&&a[i].y_2<=a[j].y_2)))v[i].push_back(j);
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=20;i++)dp[0][i]=1;
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(!check(i,j)) continue;
			for(int k=1;k<=20;k++){
				if(k!=a[j].col)dp[i][a[j].col]=min(dp[i][a[j].col],dp[i-(1<<(j-1))][k]+1);
				else dp[i][a[j].col]=min(dp[i][a[j].col],dp[i-(1<<(j-1))][k]);
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=20;i++)ans=min(ans,dp[(1<<n)-1][i]);
	cout<<ans;
}