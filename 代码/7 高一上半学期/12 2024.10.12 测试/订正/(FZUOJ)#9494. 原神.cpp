#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int a[N];
int ans;
void dfs(int x,int y){
	ans^=a[x+1]-a[y];
	if((x||y)&&x>=y&&((x<<1)<n))dfs(x<<1,y<<1);
	if(x>=y&&((x<<1|1)<n))dfs(x<<1|1,y<<1|1);
	if(((x<<1|1)>=(y<<1))&&((x<<1|1)<n))dfs(x<<1|1,y<<1);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	dfs(0,0);
	cout<<ans;
}