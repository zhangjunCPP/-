#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int a[N];
signed main() {
	freopen("ghost.in","r",stdin);
	freopen("ghost.out","w",stdout);
	int n,r,k;
	cin>>n>>r>>k;
	for(int i=1;i<=n;i++)a[i]=i;
	int ans=0;
	do {
		bool flag=true;
		for(int i=1;i<=n;i++) {
			if(i%k==0&&a[i]<a[i+1]){flag=false;break;}
			if(i%k!=0&&a[i]>=a[i+1]){flag=false;break;}
		}
		ans+=flag;
	}while(next_permutation(a+1,a+n+1));
	cout<<ans;
}