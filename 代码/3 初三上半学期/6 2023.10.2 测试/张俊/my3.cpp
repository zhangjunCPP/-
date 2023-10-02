#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
int s[N];
signed main(){
	freopen("b.in","r",stdin);
	freopen("my3.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	int ans=-1;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int sum=s[j]-s[i-1];
			int num=j-i+1;
			int tmp=0;
			double val=sum*1.0/num;
			for(int k=i;k<=j;k++) {
				if(a[k]*1.0>val) tmp++;
			}
			cout<<i<<" "<<j<<" "<<tmp<<"\n";
			ans=max(ans,tmp);
		}
	}
	cout<<ans;
}
