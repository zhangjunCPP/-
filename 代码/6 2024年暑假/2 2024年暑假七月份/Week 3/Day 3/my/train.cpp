#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
void solve(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(q--){
		int l,r;
		cin>>l>>r;
		int ans=0;
		while(r!=l){
			ans++;
			int nex=r-1;
			for(int i=r-2;i>=l;i--)if((a[r]^a[i])>(a[r]^a[nex]))nex=i;
			r=nex;
		}
		cout<<ans<<"\n";
	}
}
int main(){
	freopen("train.in","r",stdin);
	freopen("train.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}