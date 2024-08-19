#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k;
int a[N];
// int sum=0;
vector<int>ans;
int cut[N];
// bool cmp(const vector<int>&x,const vector<int>&y){return x[0]>y[0];}
void dfs(int p,int s) {
	if(n-p+1<k-s)return;
	if(p==n) {
		// sum++;
		// cout<<"sum="<<sum<<"\n";
		cut[k]=p;
		// cout<<"cut"<<":";
		// for(int i=1;i<=k;i++)cout<<cut[i]<<" ";
		// cout<<"\n";
		vector<int>tmp[25];
		for(int i=1;i<=k;i++)tmp[i].assign(a+cut[i-1]+1,a+cut[i]+1);
		// for(int i=1;i<=k;i++) {
		// 	for(int j:tmp[i])cout<<j<<" ";
		// 	cout<<"\n";
		// }
		// cout<<"------\n";
		sort(tmp+1,tmp+k+1,greater<>{});
		vector<int>tmpp;
		// for(int i=1;i<=k;i++) {
		// 	for(int j:tmp[i])cout<<j<<" ";
		// 	cout<<"\n";
		// }
		for(int i=1;i<=k;i++)for(int j:tmp[i])tmpp.push_back(j);
		ans=ans.empty()?tmpp:min(ans,tmpp);
		return;
	}
	dfs(p+1,s);
	if(s!=k-1){cut[s+1]=p;dfs(p+1,s+1);}
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	cin>>n>>k;
	if(n==k){for(int i=n;i;i--)cout<<i<<" ";return 0;}
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1,0);
	for(int i:ans)cout<<i<<" ";
}