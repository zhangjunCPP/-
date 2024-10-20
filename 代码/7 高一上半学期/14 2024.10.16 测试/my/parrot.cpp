#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int cnt[N];
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n*m;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cnt[i]=0;
	int Max=-1,sum=0;
	for(int i=1;i<=n*m;i++){
		int j=i+1;
		while(j<=n*m&&a[j]==a[i])j++;
		j--;
		// cout<<i<<" "<<j<<"\n";
		cnt[a[i]]+=(j-i+1)>>1;
		Max=max(Max,cnt[a[i]]);
		sum+=(j-i+1)>>1;
		i=j;
	}
	cout<<n*m-max(Max*2,sum)<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}