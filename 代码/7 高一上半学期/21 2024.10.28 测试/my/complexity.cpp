#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a<b){cout<<"No\n";return;}
	if(d<b){cout<<"No\n";return;}
	if(c<b&&a%b>c){cout<<"No\n";return;}
	if(c>=b&&d<b){cout<<"No\n";return;}
	if(c<b&&a%b<=c){
		if(d%b==0||(d%b==a%b)){cout<<"Yes\n";return;}
		else{cout<<"No\n";return;}
	}
	cout<<"Yes\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}