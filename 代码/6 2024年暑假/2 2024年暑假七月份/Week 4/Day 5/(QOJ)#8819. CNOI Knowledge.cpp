#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const ull p=13331;
const int N=1e3+10;
int sum[N][N];
int query(int l,int r) {
	cout<<"? "<<l<<" "<<r<<endl;
	int x;cin>>x;
	return x;
}
int ans[N];
int main() {
	int n;
	cin>>n;
	int tot=0;
	map<ull,int> mp;
	for(int i=1;i<=n;i++) {
		int l=1,r=i-1;
		int pos=0;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(query(mid,i)-sum[mid][i-1]<i-mid+1)pos=mid,l=mid+1;
			else r=mid-1;
		}
		if(pos)ans[i]=ans[pos];
		else ans[i]=++tot;
		ull Hash=0,base=1;
		for(int j=i;j;j--) {
			Hash+=ans[j]*base;
			base*=p;
			if(mp[Hash]<j)sum[mp[Hash]+1][i]++,sum[j+1][i]--;
			mp[Hash]=j;
		}
		for(int j=1;j<=i;j++)sum[j][i]+=sum[j-1][i];
		for(int j=1;j<i;j++)sum[j][i]+=sum[j][i-1];
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<endl;
}