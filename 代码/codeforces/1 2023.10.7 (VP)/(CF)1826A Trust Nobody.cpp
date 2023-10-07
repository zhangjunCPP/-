#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int l[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>l[i];
	for(int i=0;i<=n;i++) {
		int tmp=0;
		for(int j=1;j<=n;j++) if(i<l[j]) tmp++;
		if(tmp==i) {
			cout<<i<<"\n";
			return;
		}
	}
	cout<<"-1\n";
}
int main(){
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}