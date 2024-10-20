#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N];
map<int,int> sum;
int s[2][N];
void solve(){
	sum.clear();
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],sum[a[i]]++;
	if(k==0){for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";return;}
	for(int i=1;i<=n;i++)a[i]=sum[a[i]];
	if(k==1){for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";return;}
	k--;
	int opt=0;
	for(int i=1;i<=n;i++)s[opt][i]=0;
	for(int i=1;i<=n;i++)s[opt][a[i]]++;
	while(k--){
		bool flag=true;
		for(int i=1;i<=n;i++){
			s[opt^1][i]=0;
			if(a[i]!=s[opt][a[i]])flag=false;
			a[i]=s[opt][a[i]];
		}
		if(flag)break;
		for(int i=1;i<=n;i++)s[opt^1][a[i]]++;
		opt^=1;
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	cout<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}