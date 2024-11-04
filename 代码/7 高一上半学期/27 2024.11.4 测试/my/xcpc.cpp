#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int f[N],g[N];
bool flag[N];
pair<int,int>b[N];
int ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(flag[max(0,i-a[i])]){
			f[i]=g[max(0,i-a[i])]+1;
			flag[i]=true;
		}
		else f[i]=1;
		g[i]=max(g[i-1],f[i]);
		if(i>=a[i])flag[i]=true;
		flag[i]|=flag[i-1];
	}
	for(int i=1;i<=q;i++)cin>>b[i].first,b[i].second=i;
	sort(b+1,b+q+1);
	int sum=n;
	for(int i=1;i<=q;i++){
		for(;sum>0&&(a[sum]>sum?n-a[sum]+1:f[sum]+n-sum)<b[i].first;sum--){}
		ans[b[i].second]=sum;
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<" ";
	return 0;
}