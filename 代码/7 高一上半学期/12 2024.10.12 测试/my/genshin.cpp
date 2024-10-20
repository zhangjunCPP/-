#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int a[N];
// bitset<N> C;
// queue<pair<int,int>> q;
int ans;
void dfs(int x,int y){
	if(x>=n||y>x)return;
	ans^=a[x+1]-a[y];
	if(x||y)dfs(x<<1,y<<1);
	dfs(x<<1|1,y<<1|1);
	dfs(x<<1|1,y<<1);
}
int main(){
	freopen("genshin.in","r",stdin);
	freopen("genshin.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	// int ans=0;
	// C[0]=1;
	// for(int i=1;i<=n;i++){
	// 	for(int j=C._Find_first();j<i;j=C._Find_next(j))ans^=(a[i]-a[j]);
	// 	C^=(C<<1);
	// }
	// cout<<ans;
	// int ans=0;
	// q.push({0,0});
	// while(!q.empty()){
	// 	int i=q.front().first,j=q.front().second;
	// 	q.pop();
	// 	if(i>=n||j>i)continue;
	// 	ans^=a[i+1]-a[j];
	// 	if(i||j)q.push({i<<1,j<<1});
	// 	q.push({i<<1|1,j<<1|1});
	// 	q.push({i<<1|1,j<<1});
	// }
	// cout<<ans;
	dfs(0,0);
	cout<<ans;
}
/*
C[i][j]=C[i-1][j]+C[i-1][j-1]
==> C[i][j]=C[i-1][j]^C[i-1][j-1]
==> C^=(C<<1)
*/
/*
C(i,j)=C(i%2,j%2)*C(i/2,j/2)
*/