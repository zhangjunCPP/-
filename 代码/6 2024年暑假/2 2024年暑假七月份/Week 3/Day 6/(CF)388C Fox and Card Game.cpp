#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int mid[N];
int main() {
	int n;
	cin>>n;
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i++) {
		int s;
		cin>>s;
		int tmp=s/2;
		for(int j=1;j<=tmp;j++){int x;cin>>x;ans1+=x;}
		if(s&1)cin>>mid[i];
		for(int j=1;j<=tmp;j++){int x;cin>>x;ans2+=x;}
	}
	sort(mid+1,mid+n+1);
	reverse(mid+1,mid+n+1);
	for(int i=1;i<=n;i++) {
		if(i&1)ans1+=mid[i];
		else ans2+=mid[i];
	}
	cout<<ans1<<" "<<ans2;
}