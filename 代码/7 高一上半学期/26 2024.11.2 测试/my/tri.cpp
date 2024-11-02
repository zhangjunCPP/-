#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int deg[N];
signed main(){
	freopen("tri.in","r",stdin);
	freopen("tri.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		deg[u]++;
		deg[v]++;
	}
	if(n==1||n==2){
		cout<<0;
		return 0;
	}
	int ans=n*(n-1)*(n-2)/6;
	int sum=0;
	for(int i=1;i<=n;i++)sum+=(deg[i])*(n-deg[i]-1);
	ans-=sum/2;
	cout<<ans;
}