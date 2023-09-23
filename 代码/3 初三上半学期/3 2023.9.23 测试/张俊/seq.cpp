#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	int n,m,f;
	cin>>n>>m>>f;
	for(int i=1; i<=n; i++) cin>>a[i];

	int lastans=0;
	while(m--) {
		int opt;
		int l,r,x,y;
		cin>>opt;
		if(opt==1) cin>>l>>r>>x;
		else cin>>x>>y;
		if(f) {
			l^=lastans;
			r^=lastans;
			x^=lastans;
			y^=lastans;
		}
		if(opt==1) {
			for(int i=l; i<=r; i++)a[i]=x;
		} else {
			int ans=0x3f3f3f3f;
			for(int i=1; i<=n; i++) {
				for(int j=i; j>=1 ; j--) {
					if(a[i]==x&&a[j]==y) {
						ans=min(ans,i-j);
						break;
					}
				}
				for(int j=i;j<=n;j++){
					if(a[i]==x&&a[j]==y){
						ans=min(ans,j-i);
						break;
					}
				}
			}
			if(ans==0x3f3f3f3f) ans=-1;
			cout<<ans<<"\n";
			lastans=ans;
		}
	}
}

