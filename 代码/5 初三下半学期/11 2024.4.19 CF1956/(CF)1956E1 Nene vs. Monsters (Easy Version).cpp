#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int a[N];
bool check(int n){
	for(int i=0;i<n;i++)if(a[i]&&a[(i+1)%n]&&a[(i+2)%n])return true;
	return false;
}
void solve(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	if(n==2){
		while(a[0]&&a[1])a[1]=max(0ll,a[1]-a[0]),a[0]=max(0ll,a[0]-a[1]);
		if(a[0])cout<<"1\n1\n";
		else if(a[1])cout<<"1\n2\n";
		else cout<<"0\n";
		return;
	}
	while(check(n))for(int i=0;i<n;i++)a[(i+1)%n]=max(0ll,a[(i+1)%n]-a[i]);
	vector<int> ans;
	for(int i=0;i<n;i++)if(a[i]&&!a[(i-1+n)%n])ans.push_back(i+1);
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<" ";
	cout<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}