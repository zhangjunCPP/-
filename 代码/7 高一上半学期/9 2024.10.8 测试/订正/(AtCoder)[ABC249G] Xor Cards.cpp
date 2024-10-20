#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N],b[N];
int p[65];
int insert(int x){
	for(int i=60;i>=0;i--){
		if((x>>i)&1){
			if(p[i])x^=p[i];
			else{p[i]=x;return x;}
		}
	}
	return x;
}
int query(int x){
	for(int i=60;i>=30;i--)if((x>>i)&1)x^=p[i];
	for(int i=29;i>=0;i--)if(!((x>>i)&1))x^=p[i];
	if(x>=(1ll<<30))return -1;
	return x;
}
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	bool flag=false;
	for(int i=1;i<=n;i++)if(insert(a[i])<=k)flag=true;
	if(!flag){cout<<"-1";return 0;}
	memset(p,0,sizeof p);
	for(int i=1;i<=n;i++)insert((a[i]<<30)|b[i]);
	int ans=query(k<<30);
	for(int i=30;i>=0;i--){
		if((k>>i)&1){
			memset(p,0,sizeof p);
			for(int j=1;j<=n;j++)insert((a[j]>>i<<i<<30)|b[j]);
			ans=max(ans,query(((k>>i)^1)<<i<<30));
		}
	}
	cout<<ans;
	return 0;
}