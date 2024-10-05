#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N],b[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("sink.in","r",stdin);
	freopen("sink.out","w",stdout);
	int n;
	cin>>n;
	bool flag=true;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
		if(i!=1&&a[i]<a[i-1])flag=false;
	}
	if(flag){
		int ans=0;
		for(int i=1;i<=n;i++)ans+=a[i];
		for(int i=1;i<=n;i++){
			ans-=(a[n-i+1]-a[1]);
			cout<<ans<<" ";
		}
		return 0;
	}
	for(int j=1;j<=n;j++){
		int tmp=b[n];
		for(int i=n;i>=2;i--)b[i]=b[i-1];
		b[1]=tmp;
		for(int i=1;i<=n;i++)b[i]=min(b[i],a[i]);
		int ans=0;
		for(int i=1;i<=n;i++)ans+=b[i];
		cout<<ans<<" ";
	}

}