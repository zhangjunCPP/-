#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
void solve(){
	map<int,int>mp;
	int n;
	cin>>n;
	int tmp=n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	int ans=1;
	for(int i=1;i<=n;i++){
		int l=i,r=n;
		int res=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(a[mid]<=a[i]+tmp-1)res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,res-i+1);
	}
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
