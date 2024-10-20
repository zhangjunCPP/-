#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10;
const int mod=998244353;
const int INF=1e18;
int p[N];
int ans[N];
struct node{
	int x,y;
}q[N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)ans[i]=i;
	for(int i=1;i<=m;i++)cin>>q[i].x>>q[i].y;
	do{
		bool flag=true;
		for(int i=1;i<=n;i++)if(p[i]&&ans[i]!=p[i]){flag=false;break;}
		if(!flag)continue;
		for(int i=1;i<=m;i++)if(ans[q[i].x]>ans[q[i].y]){flag=false;break;}
		if(!flag)continue;
		for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
		cout<<"\n";
		return 0;
	}while(next_permutation(ans+1,ans+n+1));
	cout<<"-1";
}