#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int ans[N],nex[N];
int a[N];
int tmp[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,k,m;
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=1,r=k+1;
	nex[1]=k+1;
	for(int i=2;i<=n;i++){
		while(r+1<=n&&a[i]-a[l]>a[r+1]-a[i]) l++,r++;
		if(a[i]-a[l]>=a[r]-a[i]) nex[i]=l;
		else nex[i]=r;
	}
	for(int i=1;i<=n;i++) ans[i]=i;
	while(m){
		if(m&1)for(int i=1;i<=n;i++) ans[i]=nex[ans[i]];
		for(int i=1;i<=n;i++) tmp[i]=nex[i];
		for(int i=1;i<=n;i++) nex[i]=tmp[tmp[i]];
		m>>=1;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}